/*
 * Copyright 2017 gRPC authors.
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
 */

/*
 * Automatically generated by tools/codegen/core/gen_stats_data.py
 */

#include "src/core/lib/debug/stats_data.h"
#include <grpc/support/useful.h>
#include "src/core/lib/debug/stats.h"
#include "src/core/lib/iomgr/exec_ctx.h"
const char *grpc_stats_counter_name[GRPC_STATS_COUNTER_COUNT] = {
    "client_calls_created",
    "server_calls_created",
    "syscall_poll",
    "syscall_wait",
    "histogram_slow_lookups",
    "syscall_write",
    "syscall_read",
    "tcp_backup_pollers_created",
    "tcp_backup_poller_polls",
    "http2_op_batches",
    "http2_op_cancel",
    "http2_op_send_initial_metadata",
    "http2_op_send_message",
    "http2_op_send_trailing_metadata",
    "http2_op_recv_initial_metadata",
    "http2_op_recv_message",
    "http2_op_recv_trailing_metadata",
    "http2_pings_sent",
    "http2_writes_begun",
    "combiner_locks_initiated",
    "combiner_locks_scheduled_items",
    "combiner_locks_scheduled_final_items",
    "combiner_locks_offloaded",
    "executor_scheduled_short_items",
    "executor_scheduled_long_items",
    "executor_scheduled_to_self",
    "executor_wakeup_initiated",
    "executor_queue_drained",
    "executor_push_retries",
};
const char *grpc_stats_histogram_name[GRPC_STATS_HISTOGRAM_COUNT] = {
    "tcp_write_size", "tcp_write_iov_size", "tcp_read_size",
    "tcp_read_offer", "tcp_read_iov_size",  "http2_send_message_size",
};
const int grpc_stats_table_0[65] = {
    0,       1,       2,       3,       4,       6,       8,        11,
    15,      20,      26,      34,      44,      57,      73,       94,
    121,     155,     199,     255,     327,     419,     537,      688,
    881,     1128,    1444,    1848,    2365,    3026,    3872,     4954,
    6338,    8108,    10373,   13270,   16976,   21717,   27782,    35541,
    45467,   58165,   74409,   95189,   121772,  155778,  199281,   254933,
    326126,  417200,  533707,  682750,  873414,  1117323, 1429345,  1828502,
    2339127, 2992348, 3827987, 4896985, 6264509, 8013925, 10251880, 13114801,
    16777216};
const uint8_t grpc_stats_table_1[87] = {
    0,  0,  1,  1,  2,  3,  3,  4,  4,  5,  6,  6,  7,  8,  8,  9,  10, 11,
    11, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 19, 20, 20, 21, 22, 22, 23,
    24, 25, 25, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33, 34, 34, 35, 36,
    36, 37, 38, 39, 39, 40, 41, 41, 42, 43, 44, 44, 45, 45, 46, 47, 48, 48,
    49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 56, 57, 58, 58, 59};
const int grpc_stats_table_2[65] = {
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,
    14,  16,  18,  20,  22,  24,  27,  30,  33,  36,  39,  43,  47,
    51,  56,  61,  66,  72,  78,  85,  92,  100, 109, 118, 128, 139,
    151, 164, 178, 193, 209, 226, 244, 264, 285, 308, 333, 359, 387,
    418, 451, 486, 524, 565, 609, 656, 707, 762, 821, 884, 952, 1024};
const uint8_t grpc_stats_table_3[102] = {
    0,  0,  0,  1,  1,  1,  1,  2,  2,  3,  3,  4,  4,  5,  5,  6,  6,
    6,  7,  7,  7,  8,  8,  9,  9,  10, 11, 11, 12, 12, 13, 13, 14, 14,
    14, 15, 15, 16, 16, 17, 17, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23,
    23, 24, 24, 24, 25, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32,
    32, 33, 33, 34, 35, 35, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41,
    42, 42, 43, 44, 44, 45, 46, 46, 47, 48, 48, 49, 49, 50, 50, 51, 51};
void grpc_stats_inc_tcp_write_size(grpc_exec_ctx *exec_ctx, int value) {
  value = GPR_CLAMP(value, 0, 16777216);
  if (value < 5) {
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_WRITE_SIZE,
                             value);
    return;
  }
  union {
    double dbl;
    uint64_t uint;
  } _val, _bkt;
  _val.dbl = value;
  if (_val.uint < 4683743612465315840ull) {
    int bucket =
        grpc_stats_table_1[((_val.uint - 4617315517961601024ull) >> 50)] + 5;
    _bkt.dbl = grpc_stats_table_0[bucket];
    bucket -= (_val.uint < _bkt.uint);
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_WRITE_SIZE,
                             bucket);
    return;
  }
  GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_WRITE_SIZE,
                           grpc_stats_histo_find_bucket_slow(
                               (exec_ctx), value, grpc_stats_table_0, 64));
}
void grpc_stats_inc_tcp_write_iov_size(grpc_exec_ctx *exec_ctx, int value) {
  value = GPR_CLAMP(value, 0, 1024);
  if (value < 13) {
    GRPC_STATS_INC_HISTOGRAM((exec_ctx),
                             GRPC_STATS_HISTOGRAM_TCP_WRITE_IOV_SIZE, value);
    return;
  }
  union {
    double dbl;
    uint64_t uint;
  } _val, _bkt;
  _val.dbl = value;
  if (_val.uint < 4637863191261478912ull) {
    int bucket =
        grpc_stats_table_3[((_val.uint - 4623507967449235456ull) >> 48)] + 13;
    _bkt.dbl = grpc_stats_table_2[bucket];
    bucket -= (_val.uint < _bkt.uint);
    GRPC_STATS_INC_HISTOGRAM((exec_ctx),
                             GRPC_STATS_HISTOGRAM_TCP_WRITE_IOV_SIZE, bucket);
    return;
  }
  GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_WRITE_IOV_SIZE,
                           grpc_stats_histo_find_bucket_slow(
                               (exec_ctx), value, grpc_stats_table_2, 64));
}
void grpc_stats_inc_tcp_read_size(grpc_exec_ctx *exec_ctx, int value) {
  value = GPR_CLAMP(value, 0, 16777216);
  if (value < 5) {
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_SIZE,
                             value);
    return;
  }
  union {
    double dbl;
    uint64_t uint;
  } _val, _bkt;
  _val.dbl = value;
  if (_val.uint < 4683743612465315840ull) {
    int bucket =
        grpc_stats_table_1[((_val.uint - 4617315517961601024ull) >> 50)] + 5;
    _bkt.dbl = grpc_stats_table_0[bucket];
    bucket -= (_val.uint < _bkt.uint);
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_SIZE,
                             bucket);
    return;
  }
  GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_SIZE,
                           grpc_stats_histo_find_bucket_slow(
                               (exec_ctx), value, grpc_stats_table_0, 64));
}
void grpc_stats_inc_tcp_read_offer(grpc_exec_ctx *exec_ctx, int value) {
  value = GPR_CLAMP(value, 0, 16777216);
  if (value < 5) {
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_OFFER,
                             value);
    return;
  }
  union {
    double dbl;
    uint64_t uint;
  } _val, _bkt;
  _val.dbl = value;
  if (_val.uint < 4683743612465315840ull) {
    int bucket =
        grpc_stats_table_1[((_val.uint - 4617315517961601024ull) >> 50)] + 5;
    _bkt.dbl = grpc_stats_table_0[bucket];
    bucket -= (_val.uint < _bkt.uint);
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_OFFER,
                             bucket);
    return;
  }
  GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_OFFER,
                           grpc_stats_histo_find_bucket_slow(
                               (exec_ctx), value, grpc_stats_table_0, 64));
}
void grpc_stats_inc_tcp_read_iov_size(grpc_exec_ctx *exec_ctx, int value) {
  value = GPR_CLAMP(value, 0, 1024);
  if (value < 13) {
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_IOV_SIZE,
                             value);
    return;
  }
  union {
    double dbl;
    uint64_t uint;
  } _val, _bkt;
  _val.dbl = value;
  if (_val.uint < 4637863191261478912ull) {
    int bucket =
        grpc_stats_table_3[((_val.uint - 4623507967449235456ull) >> 48)] + 13;
    _bkt.dbl = grpc_stats_table_2[bucket];
    bucket -= (_val.uint < _bkt.uint);
    GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_IOV_SIZE,
                             bucket);
    return;
  }
  GRPC_STATS_INC_HISTOGRAM((exec_ctx), GRPC_STATS_HISTOGRAM_TCP_READ_IOV_SIZE,
                           grpc_stats_histo_find_bucket_slow(
                               (exec_ctx), value, grpc_stats_table_2, 64));
}
void grpc_stats_inc_http2_send_message_size(grpc_exec_ctx *exec_ctx,
                                            int value) {
  value = GPR_CLAMP(value, 0, 16777216);
  if (value < 5) {
    GRPC_STATS_INC_HISTOGRAM(
        (exec_ctx), GRPC_STATS_HISTOGRAM_HTTP2_SEND_MESSAGE_SIZE, value);
    return;
  }
  union {
    double dbl;
    uint64_t uint;
  } _val, _bkt;
  _val.dbl = value;
  if (_val.uint < 4683743612465315840ull) {
    int bucket =
        grpc_stats_table_1[((_val.uint - 4617315517961601024ull) >> 50)] + 5;
    _bkt.dbl = grpc_stats_table_0[bucket];
    bucket -= (_val.uint < _bkt.uint);
    GRPC_STATS_INC_HISTOGRAM(
        (exec_ctx), GRPC_STATS_HISTOGRAM_HTTP2_SEND_MESSAGE_SIZE, bucket);
    return;
  }
  GRPC_STATS_INC_HISTOGRAM((exec_ctx),
                           GRPC_STATS_HISTOGRAM_HTTP2_SEND_MESSAGE_SIZE,
                           grpc_stats_histo_find_bucket_slow(
                               (exec_ctx), value, grpc_stats_table_0, 64));
}
const int grpc_stats_histo_buckets[6] = {64, 64, 64, 64, 64, 64};
const int grpc_stats_histo_start[6] = {0, 64, 128, 192, 256, 320};
const int *const grpc_stats_histo_bucket_boundaries[6] = {
    grpc_stats_table_0, grpc_stats_table_2, grpc_stats_table_0,
    grpc_stats_table_0, grpc_stats_table_2, grpc_stats_table_0};
void (*const grpc_stats_inc_histogram[6])(grpc_exec_ctx *exec_ctx, int x) = {
    grpc_stats_inc_tcp_write_size,    grpc_stats_inc_tcp_write_iov_size,
    grpc_stats_inc_tcp_read_size,     grpc_stats_inc_tcp_read_offer,
    grpc_stats_inc_tcp_read_iov_size, grpc_stats_inc_http2_send_message_size};
