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

/* With the addition of a libuv endpoint, sockaddr.h now includes uv.h when
   using that endpoint. Because of various transitive includes in uv.h,
   including windows.h on Windows, uv.h must be included before other system
   headers. Therefore, sockaddr.h must always be included first */
#include "src/core/lib/iomgr/sockaddr.h"

#include "test/core/util/passthru_endpoint.h"

#include <inttypes.h>
#include <string.h>

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include "src/core/lib/iomgr/sockaddr.h"

#include "src/core/lib/slice/slice_internal.h"

typedef struct passthru_endpoint passthru_endpoint;

typedef struct {
  grpc_endpoint base;
  passthru_endpoint *parent;
  grpc_slice_buffer read_buffer;
  grpc_slice_buffer *on_read_out;
  grpc_closure *on_read;
  grpc_resource_user *resource_user;
} half;

struct passthru_endpoint {
  gpr_mu mu;
  int halves;
  grpc_passthru_endpoint_stats *stats;
  grpc_passthru_endpoint_stats
      dummy_stats;  // used if constructor stats == NULL
  bool shutdown;
  half client;
  half server;
};

static void me_read(grpc_exec_ctx *exec_ctx, grpc_endpoint *ep,
                    grpc_slice_buffer *slices, grpc_closure *cb) {
  half *m = (half *)ep;
  gpr_mu_lock(&m->parent->mu);
  if (m->parent->shutdown) {
    grpc_closure_sched(
        exec_ctx, cb, GRPC_ERROR_CREATE_FROM_STATIC_STRING("Already shutdown"));
  } else if (m->read_buffer.count > 0) {
    grpc_slice_buffer_swap(&m->read_buffer, slices);
    grpc_closure_sched(exec_ctx, cb, GRPC_ERROR_NONE);
  } else {
    m->on_read = cb;
    m->on_read_out = slices;
  }
  gpr_mu_unlock(&m->parent->mu);
}

static half *other_half(half *h) {
  if (h == &h->parent->client) return &h->parent->server;
  return &h->parent->client;
}

static void me_write(grpc_exec_ctx *exec_ctx, grpc_endpoint *ep,
                     grpc_slice_buffer *slices, grpc_closure *cb) {
  half *m = other_half((half *)ep);
  gpr_mu_lock(&m->parent->mu);
  grpc_error *error = GRPC_ERROR_NONE;
  m->parent->stats->num_writes++;
  if (m->parent->shutdown) {
    error = GRPC_ERROR_CREATE_FROM_STATIC_STRING("Endpoint already shutdown");
  } else if (m->on_read != NULL) {
    for (size_t i = 0; i < slices->count; i++) {
      grpc_slice_buffer_add(m->on_read_out, grpc_slice_copy(slices->slices[i]));
    }
    grpc_closure_sched(exec_ctx, m->on_read, GRPC_ERROR_NONE);
    m->on_read = NULL;
  } else {
    for (size_t i = 0; i < slices->count; i++) {
      grpc_slice_buffer_add(&m->read_buffer,
                            grpc_slice_copy(slices->slices[i]));
    }
  }
  gpr_mu_unlock(&m->parent->mu);
  grpc_closure_sched(exec_ctx, cb, error);
}

static void me_add_to_pollset(grpc_exec_ctx *exec_ctx, grpc_endpoint *ep,
                              grpc_pollset *pollset) {}

static void me_add_to_pollset_set(grpc_exec_ctx *exec_ctx, grpc_endpoint *ep,
                                  grpc_pollset_set *pollset) {}

static void me_shutdown(grpc_exec_ctx *exec_ctx, grpc_endpoint *ep,
                        grpc_error *why) {
  half *m = (half *)ep;
  gpr_mu_lock(&m->parent->mu);
  m->parent->shutdown = true;
  if (m->on_read) {
    grpc_closure_sched(
        exec_ctx, m->on_read,
        GRPC_ERROR_CREATE_REFERENCING_FROM_STATIC_STRING("Shutdown", &why, 1));
    m->on_read = NULL;
  }
  m = other_half(m);
  if (m->on_read) {
    grpc_closure_sched(
        exec_ctx, m->on_read,
        GRPC_ERROR_CREATE_REFERENCING_FROM_STATIC_STRING("Shutdown", &why, 1));
    m->on_read = NULL;
  }
  gpr_mu_unlock(&m->parent->mu);
  grpc_resource_user_shutdown(exec_ctx, m->resource_user);
  GRPC_ERROR_UNREF(why);
}

static void me_destroy(grpc_exec_ctx *exec_ctx, grpc_endpoint *ep) {
  passthru_endpoint *p = ((half *)ep)->parent;
  gpr_mu_lock(&p->mu);
  if (0 == --p->halves) {
    gpr_mu_unlock(&p->mu);
    gpr_mu_destroy(&p->mu);
    grpc_slice_buffer_destroy_internal(exec_ctx, &p->client.read_buffer);
    grpc_slice_buffer_destroy_internal(exec_ctx, &p->server.read_buffer);
    grpc_resource_user_unref(exec_ctx, p->client.resource_user);
    grpc_resource_user_unref(exec_ctx, p->server.resource_user);
    gpr_free(p);
  } else {
    gpr_mu_unlock(&p->mu);
  }
}

static char *me_get_peer(grpc_endpoint *ep) {
  passthru_endpoint *p = ((half *)ep)->parent;
  return ((half *)ep) == &p->client ? gpr_strdup("fake:mock_client_endpoint")
                                    : gpr_strdup("fake:mock_server_endpoint");
}

static int me_get_fd(grpc_endpoint *ep) { return -1; }

static grpc_resource_user *me_get_resource_user(grpc_endpoint *ep) {
  half *m = (half *)ep;
  return m->resource_user;
}

static const grpc_endpoint_vtable vtable = {
    me_read,     me_write,   me_add_to_pollset,    me_add_to_pollset_set,
    me_shutdown, me_destroy, me_get_resource_user, me_get_peer,
    me_get_fd,
};

static void half_init(half *m, passthru_endpoint *parent,
                      grpc_resource_quota *resource_quota,
                      const char *half_name) {
  m->base.vtable = &vtable;
  m->parent = parent;
  grpc_slice_buffer_init(&m->read_buffer);
  m->on_read = NULL;
  char *name;
  gpr_asprintf(&name, "passthru_endpoint_%s_%" PRIxPTR, half_name,
               (intptr_t)parent);
  m->resource_user = grpc_resource_user_create(resource_quota, name);
  gpr_free(name);
}

void grpc_passthru_endpoint_create(grpc_endpoint **client,
                                   grpc_endpoint **server,
                                   grpc_resource_quota *resource_quota,
                                   grpc_passthru_endpoint_stats *stats) {
  passthru_endpoint *m = gpr_malloc(sizeof(*m));
  m->halves = 2;
  m->shutdown = 0;
  m->stats = stats == NULL ? &m->dummy_stats : stats;
  memset(m->stats, 0, sizeof(*m->stats));
  half_init(&m->client, m, resource_quota, "client");
  half_init(&m->server, m, resource_quota, "server");
  gpr_mu_init(&m->mu);
  *client = &m->client.base;
  *server = &m->server.base;
}
