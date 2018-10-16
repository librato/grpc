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

#ifndef GRPCPP_IMPL_CODEGEN_INTERCEPTOR_H
#define GRPCPP_IMPL_CODEGEN_INTERCEPTOR_H

#include <grpc/impl/codegen/grpc_types.h>
#include <grpcpp/impl/codegen/byte_buffer.h>
#include <grpcpp/impl/codegen/config.h>
#include <grpcpp/impl/codegen/core_codegen_interface.h>
#include <grpcpp/impl/codegen/metadata_map.h>

// struct grpc_byte_buffer;
// struct grpc_status_code;
// struct grpc_metadata;

namespace grpc {

class Status;

namespace experimental {
class InterceptedMessage {
 public:
  template <class M>
  bool Extract(M* msg);  // returns false if definitely invalid extraction
  template <class M>
  M* MutableExtract();
  uint64_t length();  // length on wire
};

enum class InterceptionHookPoints {
  /* The first two in this list are for clients and servers */
  PRE_SEND_INITIAL_METADATA,
  PRE_SEND_MESSAGE,
  PRE_SEND_STATUS /* server only */,
  PRE_SEND_CLOSE /* client only */,
  /* The following three are for hijacked clients only and can only be
     registered by the global interceptor */
  PRE_RECV_INITIAL_METADATA,
  PRE_RECV_MESSAGE,
  PRE_RECV_STATUS,
  /* The following two are for all clients and servers */
  POST_RECV_INITIAL_METADATA,
  POST_RECV_MESSAGE,
  POST_RECV_STATUS /* client only */,
  POST_RECV_CLOSE /* server only */,
  NUM_INTERCEPTION_HOOKS
};

class InterceptorBatchMethods {
 public:
  virtual ~InterceptorBatchMethods(){};
  // Queries to check whether the current batch has an interception hook point
  // of type \a type
  virtual bool QueryInterceptionHookPoint(InterceptionHookPoints type) = 0;
  // Calling this will signal that the interceptor is done intercepting the
  // current batch of the RPC
  virtual void Proceed() = 0;
  // Calling this indicates that the interceptor has hijacked the RPC (only
  // valid if the batch contains send_initial_metadata on the client side)
  virtual void Hijack() = 0;

  virtual void AddInterceptionHookPoint(InterceptionHookPoints type) = 0;

  virtual ByteBuffer* GetSendMessage() = 0;

  virtual std::multimap<grpc::string, grpc::string>*
  GetSendInitialMetadata() = 0;

  virtual Status GetSendStatus() = 0;

  virtual void ModifySendStatus(const Status& status) = 0;

  virtual std::multimap<grpc::string, grpc::string>*
  GetSendTrailingMetadata() = 0;

  virtual void* GetRecvMessage() = 0;

  virtual std::multimap<grpc::string_ref, grpc::string_ref>*
  GetRecvInitialMetadata() = 0;

  virtual Status* GetRecvStatus() = 0;

  virtual std::multimap<grpc::string_ref, grpc::string_ref>*
  GetRecvTrailingMetadata() = 0;

  virtual void SetSendMessage(ByteBuffer* buf) = 0;

  virtual void SetSendInitialMetadata(
      std::multimap<grpc::string, grpc::string>* metadata) = 0;

  virtual void SetSendStatus(grpc_status_code* code,
                             grpc::string* error_details,
                             grpc::string* error_message) = 0;

  virtual void SetSendTrailingMetadata(
      std::multimap<grpc::string, grpc::string>* metadata) = 0;

  virtual void SetRecvMessage(void* message) = 0;

  virtual void SetRecvInitialMetadata(internal::MetadataMap* map) = 0;

  virtual void SetRecvStatus(Status* status) = 0;

  virtual void SetRecvTrailingMetadata(internal::MetadataMap* map) = 0;
};

class Interceptor {
 public:
  virtual ~Interceptor() {}

  virtual void Intercept(InterceptorBatchMethods* methods) = 0;
};

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_IMPL_CODEGEN_INTERCEPTOR_H
