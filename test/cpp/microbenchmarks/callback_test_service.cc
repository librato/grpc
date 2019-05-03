/*
 *
 * Copyright 2019 gRPC authors.
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

#include "test/cpp/microbenchmarks/callback_test_service.h"

namespace grpc {
namespace testing {
namespace {

grpc::string ToString(const grpc::string_ref& r) {
  return grpc::string(r.data(), r.size());
}

int GetIntValueFromMetadataHelper(
    const char* key,
    const std::multimap<grpc::string_ref, grpc::string_ref>& metadata,
    int default_value) {
  if (metadata.find(key) != metadata.end()) {
    std::istringstream iss(ToString(metadata.find(key)->second));
    iss >> default_value;
  }

  return default_value;
}

int GetIntValueFromMetadata(
    const char* key,
    const std::multimap<grpc::string_ref, grpc::string_ref>& metadata,
    int default_value) {
  return GetIntValueFromMetadataHelper(key, metadata, default_value);
}
}  // namespace

void CallbackStreamingTestService::Echo(
    ServerContext* context, const EchoRequest* request, EchoResponse* response,
    experimental::ServerCallbackRpcController* controller) {
  int response_msgs_size = GetIntValueFromMetadata(
      kServerMessageSize, context->client_metadata(), 0);
  if (response_msgs_size > 0) {
    response->set_message(std::string(response_msgs_size, 'a'));
  } else {
    response->set_message("");
  }
  controller->Finish(Status::OK);
}

experimental::ServerBidiReactor<EchoRequest, EchoResponse>*
CallbackStreamingTestService::BidiStream() {
  class Reactor
      : public experimental::ServerBidiReactor<EchoRequest, EchoResponse> {
   public:
    Reactor() {}
    void OnStarted(ServerContext* context) override {
      ctx_ = context;
      server_write_last_ = GetIntValueFromMetadata(
          kServerFinishAfterNReads, context->client_metadata(), 0);
      message_size_ = GetIntValueFromMetadata(kServerMessageSize,
                                              context->client_metadata(), 0);
      StartRead(&request_);
    }
    void OnDone() override {
      GPR_ASSERT(finished_);
      delete this;
    }
    void OnCancel() override {}
    void OnReadDone(bool ok) override {
      if (!ok) {
        return;
      }
      num_msgs_read_++;
      if (message_size_ > 0) {
        response_.set_message(std::string(message_size_, 'a'));
      } else {
        response_.set_message("");
      }
      if (num_msgs_read_ == server_write_last_) {
        StartWriteLast(&response_, WriteOptions());
      } else {
        StartWrite(&response_);
      }
    }
    void OnWriteDone(bool ok) override {
      if (!ok) {
        return;
      }
      if (num_msgs_read_ < server_write_last_) {
        StartRead(&request_);
      } else {
        Finish(::grpc::Status::OK);
        finished_ = true;
      }
    }

   private:
    ServerContext* ctx_;
    EchoRequest request_;
    EchoResponse response_;
    int num_msgs_read_{0};
    int server_write_last_;
    int message_size_;
    bool finished_{false};
  };

  return new Reactor;
}
}  // namespace testing
}  // namespace grpc
