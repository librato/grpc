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

#include "src/core/lib/iomgr/combiner.h"

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/thd.h>
#include <grpc/support/useful.h>

#include "test/core/util/test_config.h"

static void test_no_op(void) {
  gpr_log(GPR_DEBUG, "test_no_op");
  grpc_exec_ctx exec_ctx = GRPC_EXEC_CTX_INIT;
  GRPC_COMBINER_UNREF(&exec_ctx, grpc_combiner_create(NULL), "test_no_op");
  grpc_exec_ctx_finish(&exec_ctx);
}

static void set_bool_to_true(grpc_exec_ctx *exec_ctx, void *value,
                             grpc_error *error) {
  *(bool *)value = true;
}

static void test_execute_one(void) {
  gpr_log(GPR_DEBUG, "test_execute_one");

  grpc_combiner *lock = grpc_combiner_create(NULL);
  bool done = false;
  grpc_exec_ctx exec_ctx = GRPC_EXEC_CTX_INIT;
  grpc_closure_sched(&exec_ctx,
                     grpc_closure_create(set_bool_to_true, &done,
                                         grpc_combiner_scheduler(lock, false)),
                     GRPC_ERROR_NONE);
  grpc_exec_ctx_flush(&exec_ctx);
  GPR_ASSERT(done);
  GRPC_COMBINER_UNREF(&exec_ctx, lock, "test_execute_one");
  grpc_exec_ctx_finish(&exec_ctx);
}

typedef struct {
  size_t ctr;
  grpc_combiner *lock;
} thd_args;

typedef struct {
  size_t *ctr;
  size_t value;
} ex_args;

static void check_one(grpc_exec_ctx *exec_ctx, void *a, grpc_error *error) {
  ex_args *args = a;
  GPR_ASSERT(*args->ctr == args->value - 1);
  *args->ctr = args->value;
  gpr_free(a);
}

static void execute_many_loop(void *a) {
  thd_args *args = a;
  grpc_exec_ctx exec_ctx = GRPC_EXEC_CTX_INIT;
  size_t n = 1;
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10000; j++) {
      ex_args *c = gpr_malloc(sizeof(*c));
      c->ctr = &args->ctr;
      c->value = n++;
      grpc_closure_sched(
          &exec_ctx, grpc_closure_create(check_one, c, grpc_combiner_scheduler(
                                                           args->lock, false)),
          GRPC_ERROR_NONE);
      grpc_exec_ctx_flush(&exec_ctx);
    }
    // sleep for a little bit, to test a combiner draining and another thread
    // picking it up
    gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(100));
  }
  grpc_exec_ctx_finish(&exec_ctx);
}

static void test_execute_many(void) {
  gpr_log(GPR_DEBUG, "test_execute_many");

  grpc_combiner *lock = grpc_combiner_create(NULL);
  gpr_thd_id thds[100];
  thd_args ta[GPR_ARRAY_SIZE(thds)];
  for (size_t i = 0; i < GPR_ARRAY_SIZE(thds); i++) {
    gpr_thd_options options = gpr_thd_options_default();
    gpr_thd_options_set_joinable(&options);
    ta[i].ctr = 0;
    ta[i].lock = lock;
    GPR_ASSERT(gpr_thd_new(&thds[i], execute_many_loop, &ta[i], &options));
  }
  for (size_t i = 0; i < GPR_ARRAY_SIZE(thds); i++) {
    gpr_thd_join(thds[i]);
  }
  grpc_exec_ctx exec_ctx = GRPC_EXEC_CTX_INIT;
  GRPC_COMBINER_UNREF(&exec_ctx, lock, "test_execute_many");
  grpc_exec_ctx_finish(&exec_ctx);
}

static bool got_in_finally = false;

static void in_finally(grpc_exec_ctx *exec_ctx, void *arg, grpc_error *error) {
  got_in_finally = true;
}

static void add_finally(grpc_exec_ctx *exec_ctx, void *arg, grpc_error *error) {
  grpc_closure_sched(exec_ctx, grpc_closure_create(
                                   in_finally, NULL,
                                   grpc_combiner_finally_scheduler(arg, false)),
                     GRPC_ERROR_NONE);
}

static void test_execute_finally(void) {
  gpr_log(GPR_DEBUG, "test_execute_finally");

  grpc_combiner *lock = grpc_combiner_create(NULL);
  grpc_exec_ctx exec_ctx = GRPC_EXEC_CTX_INIT;
  grpc_closure_sched(&exec_ctx,
                     grpc_closure_create(add_finally, lock,
                                         grpc_combiner_scheduler(lock, false)),
                     GRPC_ERROR_NONE);
  grpc_exec_ctx_flush(&exec_ctx);
  GPR_ASSERT(got_in_finally);
  GRPC_COMBINER_UNREF(&exec_ctx, lock, "test_execute_finally");
  grpc_exec_ctx_finish(&exec_ctx);
}

int main(int argc, char **argv) {
  grpc_test_init(argc, argv);
  grpc_init();
  test_no_op();
  test_execute_one();
  test_execute_finally();
  test_execute_many();
  grpc_shutdown();

  return 0;
}
