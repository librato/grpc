/*
 *
 * Copyright 2018 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#import <Foundation/Foundation.h>

#include <grpc/impl/codegen/grpc_types.h>

NS_ASSUME_NONNULL_BEGIN

/** A factory interface which generates new channel. */
@protocol GRPCChannelFactory

/** Create a channel with specific channel args to a specific host. */
- (grpc_channel * _Nullable)createChannelWithHost:(NSString *)host
                                     channelArgs:(NSDictionary * _Nullable)args;

@end

NS_ASSUME_NONNULL_END
