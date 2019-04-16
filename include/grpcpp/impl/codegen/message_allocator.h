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

#ifndef GRPCPP_IMPL_CODEGEN_MESSAGE_ALLOCATOR_H_
#define GRPCPP_IMPL_CODEGEN_MESSAGE_ALLOCATOR_H_

namespace grpc {

// This is per rpc struct for the allocator. We can potentially put the grpc
// call arena in here in the future.
template <typename RequestT, typename ResponseT>
struct RpcAllocatorInfo {
  RequestT* request = nullptr;
  ResponseT* response = nullptr;
  // per rpc allocator internal state. MessageAllocator can set it when
  // AllocateMessages is called and use it later.
  void* allocator_state = nullptr;
};

// Implementations need to be thread-safe
template <typename RequestT, typename ResponseT>
class MessageAllocator {
 public:
  virtual ~MessageAllocator() = default;
  // Allocate both request and response
  virtual void AllocateMessages(
      RpcAllocatorInfo<RequestT, ResponseT>* info) = 0;
  // Optional: deallocate request early, called by
  // ServerCallbackRpcController::ReleaseRequest
  virtual void DeallocateRequest(RpcAllocatorInfo<RequestT, ResponseT>* info) {}
  // Deallocate response and request (if applicable)
  virtual void DeallocateMessages(
      RpcAllocatorInfo<RequestT, ResponseT>* info) = 0;
};

}  // namespace grpc

#endif  // GRPCPP_IMPL_CODEGEN_MESSAGE_ALLOCATOR_H_
