/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#import "GRXBufferedPipe.h"

@interface GRXBufferedPipe ()
@property(atomic) id<GRXWriteable> writeable;
@property(atomic) BOOL inputIsFinished;
@end

@implementation GRXBufferedPipe {
  NSError *_errorOrNil;
  dispatch_queue_t _writeQueue;
  dispatch_once_t _finishQueue;
}

@synthesize state = _state;

+ (instancetype)pipe {
  return [[self alloc] init];
}

- (instancetype)init {
  if (self = [super init]) {
    _state = GRXWriterStateNotStarted;
    _writeQueue = dispatch_queue_create(NULL, DISPATCH_QUEUE_SERIAL);
    self.inputIsFinished = NO;
    dispatch_suspend(_writeQueue);
  }
  return self;
}

#pragma mark GRXWriteable implementation

- (void)writeValue:(id)value {
  if (self.inputIsFinished) {
    return;
  }
  if ([value respondsToSelector:@selector(copy)]) {
    // Even if we're paused and with enqueued values, we can't excert back-pressure to our writer.
    // So just buffer the new value.
    // We need a copy, so that it doesn't mutate before it's written at the other end of the pipe.
    value = [value copy];
  }
  __weak GRXBufferedPipe *weakSelf = self;
  dispatch_async(_writeQueue, ^(void) {
    GRXBufferedPipe *strongSelf = weakSelf;
    if (strongSelf && strongSelf.writeable) {
      [strongSelf.writeable writeValue:value];
    }
  });
}

- (void)writesFinishedWithError:(NSError *)errorOrNil {
  if (self.inputIsFinished) {
    return;
  }
  self.inputIsFinished = YES;
  if (errorOrNil) {
    // No need to write pending values.
    dispatch_once(&_finishQueue, ^{
      _errorOrNil = errorOrNil;
      [self finishWithError:_errorOrNil];
    });
  } else {
    dispatch_once(&_finishQueue, ^{
      __weak GRXBufferedPipe *weakSelf = self;
      dispatch_async(_writeQueue, ^{
        GRXBufferedPipe *strongSelf = weakSelf;
        if (strongSelf) {
          [strongSelf finishWithError:nil];
        }
      });
    });
  }
}

#pragma mark GRXWriter implementation

- (void)setState:(GRXWriterState)newState {
  @synchronized (self) {
    // Manual transitions are only allowed from the started or paused states.
    if (_state == GRXWriterStateNotStarted || _state == GRXWriterStateFinished) {
      return;
    }

    switch (newState) {
      case GRXWriterStateFinished:
        if (_state == GRXWriterStatePaused) {
          dispatch_resume(_writeQueue);
        }
        _state = newState;
        // Per GRXWriter's contract, setting the state to Finished manually means one doesn't wish the
        // writeable to be messaged anymore.
        _writeable = nil;
        return;
      case GRXWriterStatePaused:
        if (_state == GRXWriterStateStarted) {
          _state = newState;
          dispatch_suspend(_writeQueue);
        }
        return;
      case GRXWriterStateStarted:
        if (_state == GRXWriterStatePaused) {
          _state = newState;
          dispatch_resume(_writeQueue);
        }
        return;
      case GRXWriterStateNotStarted:
        return;
    }
  }
}

- (void)startWithWriteable:(id<GRXWriteable>)writeable {
  _state = GRXWriterStateStarted;
  _writeable = writeable;
  dispatch_resume(_writeQueue);
}

- (void)finishWithError:(NSError *)errorOrNil {
  id<GRXWriteable> writeable = self.writeable;
  self.writeable = nil;
  self.state = GRXWriterStateFinished;
  dispatch_async(_writeQueue, ^{
    [writeable writesFinishedWithError:errorOrNil];
  });
}

@end
