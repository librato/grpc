/*
 *
 * Copyright 2016 gRPC authors.
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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>

#include "src/core/lib/slice/percent_encoding.h"
#include "test/core/util/memory_counters.h"

bool squelch = true;
bool leak_check = true;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  grpc_core::testing::LeakDetector leak_detector(true);
  grpc_init();
  grpc_slice input = grpc_slice_from_copied_buffer((const char*)data, size);
  grpc_slice output;
  if (grpc_strict_percent_decode_slice(
          input, grpc_url_percent_encoding_unreserved_bytes, &output)) {
    grpc_slice_unref(output);
  }
  if (grpc_strict_percent_decode_slice(
          input, grpc_compatible_percent_encoding_unreserved_bytes, &output)) {
    grpc_slice_unref(output);
  }
  grpc_slice_unref(grpc_permissive_percent_decode_slice(input));
  grpc_slice_unref(input);
  grpc_shutdown_blocking();
  return 0;
}
