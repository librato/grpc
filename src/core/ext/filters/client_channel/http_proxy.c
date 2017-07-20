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

#include "src/core/ext/filters/client_channel/http_proxy.h"

#include <stdbool.h>
#include <string.h>

#include <grpc/support/alloc.h>
#include <grpc/support/host_port.h>
#include <grpc/support/log.h>
#include <grpc/support/string_util.h>

#include "src/core/ext/filters/client_channel/http_connect_handshaker.h"
#include "src/core/ext/filters/client_channel/proxy_mapper_registry.h"
#include "src/core/ext/filters/client_channel/uri_parser.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/support/env.h"
#include "src/core/lib/support/string.h"

static char* grpc_get_http_proxy_server(grpc_exec_ctx* exec_ctx) {
  char* uri_str = gpr_getenv("http_proxy");
  if (uri_str == NULL) return NULL;
  grpc_uri* uri =
      grpc_uri_parse(exec_ctx, uri_str, false /* suppress_errors */);
  char* proxy_name = NULL;
  if (uri == NULL || uri->authority == NULL) {
    gpr_log(GPR_ERROR, "cannot parse value of 'http_proxy' env var");
    goto done;
  }
  if (strcmp(uri->scheme, "http") != 0) {
    gpr_log(GPR_ERROR, "'%s' scheme not supported in proxy URI", uri->scheme);
    goto done;
  }
  if (strchr(uri->authority, '@') != NULL) {
    gpr_log(GPR_ERROR, "userinfo not supported in proxy URI");
    goto done;
  }
  proxy_name = gpr_strdup(uri->authority);
done:
  gpr_free(uri_str);
  grpc_uri_destroy(uri);
  return proxy_name;
}

static bool proxy_mapper_map_name(grpc_exec_ctx* exec_ctx,
                                  grpc_proxy_mapper* mapper,
                                  const char* server_uri,
                                  const grpc_channel_args* args,
                                  char** name_to_resolve,
                                  grpc_channel_args** new_args) {
  *name_to_resolve = grpc_get_http_proxy_server(exec_ctx);
  if (*name_to_resolve == NULL) return false;
  grpc_uri* uri =
      grpc_uri_parse(exec_ctx, server_uri, false /* suppress_errors */);
  if (uri == NULL || uri->path[0] == '\0') {
    gpr_log(GPR_ERROR,
            "'http_proxy' environment variable set, but cannot "
            "parse server URI '%s' -- not using proxy",
            server_uri);
    if (uri != NULL) grpc_uri_destroy(uri);
    return false;
  }
  if (strcmp(uri->scheme, "unix") == 0) {
    gpr_log(GPR_INFO, "not using proxy for Unix domain socket '%s'",
            server_uri);
    grpc_uri_destroy(uri);
    return false;
  }
  char* no_proxy_str = gpr_getenv("no_proxy");
  if (no_proxy_str != NULL) {
    static const char* NO_PROXY_SEPARATOR = ",";
    bool use_proxy = true;
    char* server_host;
    char* server_port;
    if (!gpr_split_host_port(uri->path[0] == '/' ? uri->path + 1 : uri->path,
                             &server_host, &server_port)) {
      gpr_log(GPR_INFO,
              "unable to split host and port, not checking no_proxy list for "
              "host '%s'",
              server_uri);
    } else {
      size_t uri_len = strlen(server_host);
      char** no_proxy_hosts;
      size_t num_no_proxy_hosts;
      gpr_string_split(no_proxy_str, NO_PROXY_SEPARATOR, &no_proxy_hosts,
                       &num_no_proxy_hosts);
      for (size_t i = 0; i < num_no_proxy_hosts; i++) {
        char* no_proxy_entry = no_proxy_hosts[i];
        size_t no_proxy_len = strlen(no_proxy_entry);
        if (no_proxy_len <= uri_len &&
            gpr_stricmp(no_proxy_entry, &server_host[uri_len - no_proxy_len]) ==
                0) {
          gpr_log(GPR_INFO, "not using proxy for host in no_proxy list '%s'",
                  server_uri);
          use_proxy = false;
          break;
        }
      }
      for (size_t i = 0; i < num_no_proxy_hosts; i++) {
        gpr_free(no_proxy_hosts[i]);
      }
      gpr_free(no_proxy_hosts);
      gpr_free(server_host);
      gpr_free(server_port);
      if (!use_proxy) {
        grpc_uri_destroy(uri);
        gpr_free(*name_to_resolve);
        *name_to_resolve = NULL;
        return false;
      }
    }
  }
  grpc_arg new_arg = grpc_channel_arg_string_create(
      GRPC_ARG_HTTP_CONNECT_SERVER,
      uri->path[0] == '/' ? uri->path + 1 : uri->path);
  *new_args = grpc_channel_args_copy_and_add(args, &new_arg, 1);
  grpc_uri_destroy(uri);
  return true;
}

static bool proxy_mapper_map_address(grpc_exec_ctx* exec_ctx,
                                     grpc_proxy_mapper* mapper,
                                     const grpc_resolved_address* address,
                                     const grpc_channel_args* args,
                                     grpc_resolved_address** new_address,
                                     grpc_channel_args** new_args) {
  return false;
}

static void proxy_mapper_destroy(grpc_proxy_mapper* mapper) {}

static const grpc_proxy_mapper_vtable proxy_mapper_vtable = {
    proxy_mapper_map_name, proxy_mapper_map_address, proxy_mapper_destroy};

static grpc_proxy_mapper proxy_mapper = {&proxy_mapper_vtable};

void grpc_register_http_proxy_mapper() {
  grpc_proxy_mapper_register(true /* at_start */, &proxy_mapper);
}
