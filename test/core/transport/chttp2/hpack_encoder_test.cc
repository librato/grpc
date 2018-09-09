/*
 *
 * Copyright 2015 gRPC authors.
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

#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"

#include <stdio.h>
#include <string.h>

#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/string_util.h>

#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/lib/gpr/string.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/lib/transport/metadata.h"
#include "test/core/util/parse_hexstring.h"
#include "test/core/util/slice_splitter.h"
#include "test/core/util/test_config.h"

#define TEST(x) run_test(x, #x)

grpc_chttp2_hpack_compressor g_compressor;
int g_failure = 0;

void** to_delete = nullptr;
size_t num_to_delete = 0;
size_t cap_to_delete = 0;

typedef struct {
  bool eof;
  bool use_true_binary_metadata;
  bool only_intern_key;
} verify_params;

/* verify that the output generated by encoding the stream matches the
   hexstring passed in */
static void verify(const verify_params params, const char* expected,
                   size_t nheaders, ...) {
  grpc_slice_buffer output;
  grpc_slice merged;
  grpc_slice expect = parse_hexstring(expected);
  size_t i;
  va_list l;
  grpc_linked_mdelem* e =
      static_cast<grpc_linked_mdelem*>(gpr_zalloc(sizeof(*e) * nheaders));
  grpc_metadata_batch b;

  grpc_metadata_batch_init(&b);

  va_start(l, nheaders);
  for (i = 0; i < nheaders; i++) {
    char* key = va_arg(l, char*);
    char* value = va_arg(l, char*);
    if (i) {
      e[i - 1].next = &e[i];
      e[i].prev = &e[i - 1];
    }
    grpc_slice value_slice = grpc_slice_from_static_string(value);
    if (!params.only_intern_key) {
      value_slice = grpc_slice_intern(value_slice);
    }
    e[i].md = grpc_mdelem_from_slices(
        grpc_slice_intern(grpc_slice_from_static_string(key)), value_slice);
  }
  e[0].prev = nullptr;
  e[nheaders - 1].next = nullptr;
  va_end(l);

  b.list.head = &e[0];
  b.list.tail = &e[nheaders - 1];
  b.list.count = nheaders;

  if (cap_to_delete == num_to_delete) {
    cap_to_delete = GPR_MAX(2 * cap_to_delete, 1000);
    to_delete = static_cast<void**>(
        gpr_realloc(to_delete, sizeof(*to_delete) * cap_to_delete));
  }
  to_delete[num_to_delete++] = e;

  grpc_slice_buffer_init(&output);

  grpc_transport_one_way_stats stats;
  memset(&stats, 0, sizeof(stats));
  grpc_encode_header_options hopt = {
      0xdeadbeef,                      /* stream_id */
      params.eof,                      /* is_eof */
      params.use_true_binary_metadata, /* use_true_binary_metadata */
      16384,                           /* max_frame_size */
      &stats                           /* stats */
  };
  grpc_chttp2_encode_header(&g_compressor, nullptr, 0, &b, &hopt, &output);
  merged = grpc_slice_merge(output.slices, output.count);
  grpc_slice_buffer_destroy_internal(&output);
  grpc_metadata_batch_destroy(&b);

  if (!grpc_slice_eq(merged, expect)) {
    char* expect_str = grpc_dump_slice(expect, GPR_DUMP_HEX | GPR_DUMP_ASCII);
    char* got_str = grpc_dump_slice(merged, GPR_DUMP_HEX | GPR_DUMP_ASCII);
    gpr_log(GPR_ERROR, "mismatched output for %s", expected);
    gpr_log(GPR_ERROR, "EXPECT: %s", expect_str);
    gpr_log(GPR_ERROR, "GOT:    %s", got_str);
    gpr_free(expect_str);
    gpr_free(got_str);
    g_failure = 1;
  }

  grpc_slice_unref_internal(merged);
  grpc_slice_unref_internal(expect);
}

static void test_basic_headers() {
  int i;

  verify_params params = {
      false,
      false,
      false,
  };
  verify(params, "000005 0104 deadbeef 40 0161 0161", 1, "a", "a");
  verify(params, "000001 0104 deadbeef be", 1, "a", "a");
  verify(params, "000001 0104 deadbeef be", 1, "a", "a");
  verify(params, "000006 0104 deadbeef be 40 0162 0163", 2, "a", "a", "b", "c");
  verify(params, "000002 0104 deadbeef bf be", 2, "a", "a", "b", "c");
  verify(params, "000004 0104 deadbeef 7f 00 0164", 1, "a", "d");

  /* flush out what's there to make a few values look very popular */
  for (i = 0; i < 350; i++) {
    verify(params, "000003 0104 deadbeef c0 bf be", 3, "a", "a", "b", "c", "a",
           "d");
  }

  verify(params, "000006 0104 deadbeef c0 00 016b 0176", 2, "a", "a", "k", "v");
  /* this could be 000004 0104 deadbeef 0f 30 0176 also */
  verify(params, "000004 0104 deadbeef 0f 2f 0176", 1, "a", "v");
}

static void encode_int_to_str(int i, char* p) {
  p[0] = static_cast<char>('a' + i % 26);
  i /= 26;
  GPR_ASSERT(i < 26);
  p[1] = static_cast<char>('a' + i);
  p[2] = 0;
}

static void test_decode_table_overflow() {
  // Decrease the default table size to make decode table overflow easier.
  grpc_chttp2_hpack_compressor_set_max_table_size(&g_compressor, 1024);
  int i;
  char key[3], value[3];
  char* expect;

  verify_params params = {
      false,
      false,
      false,
  };

  for (i = 0; i < 29; i++) {
    encode_int_to_str(i, key);
    encode_int_to_str(i + 1, value);
    if (i == 0) {
      // 3fe107 corresponds to the table size update.
      gpr_asprintf(&expect,
                   "00000a 0104 deadbeef 3fe107 40 02%02x%02x 02%02x%02x",
                   key[0], key[1], value[0], value[1]);
      verify(params, expect, 1, key, value);
    } else {
      gpr_asprintf(&expect,
                   "000008 0104 deadbeef %02x 40 02%02x%02x 02%02x%02x",
                   0x80 + 61 + i, key[0], key[1], value[0], value[1]);
      verify(params, expect, 2, "aa", "ba", key, value);
    }
    gpr_free(expect);
  }

  /* if the above passes, then we must have just knocked this pair out of the
     decoder stack, and so we'll be forced to re-encode it */
  verify(params, "000007 0104 deadbeef 40 026161 026261", 1, "aa", "ba");
}

static void verify_table_size_change_match_elem_size(const char* key,
                                                     const char* value,
                                                     bool use_true_binary) {
  grpc_slice_buffer output;
  grpc_mdelem elem = grpc_mdelem_from_slices(
      grpc_slice_intern(grpc_slice_from_static_string(key)),
      grpc_slice_intern(grpc_slice_from_static_string(value)));
  size_t elem_size = grpc_mdelem_get_size_in_hpack_table(elem, use_true_binary);
  size_t initial_table_size = g_compressor.table_size;
  grpc_linked_mdelem* e =
      static_cast<grpc_linked_mdelem*>(gpr_zalloc(sizeof(*e)));
  grpc_metadata_batch b;
  grpc_metadata_batch_init(&b);
  e[0].md = elem;
  e[0].prev = nullptr;
  e[0].next = nullptr;
  b.list.head = &e[0];
  b.list.tail = &e[0];
  b.list.count = 1;
  grpc_slice_buffer_init(&output);

  grpc_transport_one_way_stats stats;
  memset(&stats, 0, sizeof(stats));
  grpc_encode_header_options hopt = {
      0xdeadbeef,      /* stream_id */
      false,           /* is_eof */
      use_true_binary, /* use_true_binary_metadata */
      16384,           /* max_frame_size */
      &stats /* stats */};
  grpc_chttp2_encode_header(&g_compressor, nullptr, 0, &b, &hopt, &output);
  grpc_slice_buffer_destroy_internal(&output);
  grpc_metadata_batch_destroy(&b);

  GPR_ASSERT(g_compressor.table_size == elem_size + initial_table_size);
  gpr_free(e);
}

static void test_encode_header_size() {
  verify_table_size_change_match_elem_size("hello", "world", false);
  verify_table_size_change_match_elem_size("hello-bin", "world", false);
  verify_table_size_change_match_elem_size("true-binary-bin",
                                           "I_am_true_binary_value", true);
}

static void test_interned_key_indexed() {
  int i;
  verify_params params = {false, false, true};
  verify(params, "000009 0104 deadbeef 40 0161 0162 0f2f 0163", 2, "a", "b",
         "a", "c");
  for (i = 0; i < 10; i++) {
    verify(params, "000008 0104 deadbeef 0f2f 0162 0f2f 0163", 2, "a", "b", "a",
           "c");
  }
}

static void run_test(void (*test)(), const char* name) {
  gpr_log(GPR_INFO, "RUN TEST: %s", name);
  grpc_core::ExecCtx exec_ctx;
  grpc_chttp2_hpack_compressor_init(&g_compressor);
  test();
  grpc_chttp2_hpack_compressor_destroy(&g_compressor);
}

int main(int argc, char** argv) {
  size_t i;
  grpc_test_only_set_slice_hash_seed(0);
  grpc_test_init(argc, argv);
  grpc_init();
  TEST(test_basic_headers);
  TEST(test_decode_table_overflow);
  TEST(test_encode_header_size);
  TEST(test_interned_key_indexed);
  grpc_shutdown();
  for (i = 0; i < num_to_delete; i++) {
    gpr_free(to_delete[i]);
  }
  return g_failure;
}
