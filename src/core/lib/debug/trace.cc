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

#include "src/core/lib/debug/trace.h"

#include <string.h>

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include "src/core/lib/support/env.h"

int grpc_tracer_set_enabled(const char *name, int enabled);

namespace grpc_core {

Tracer::Tracer(bool default_enabled, const char *name)
    : next_tracer_(root_tracer_), name_(name), value_(default_enabled) {
  root_tracer_ = this;
}

void Tracer::List() {
  gpr_log(GPR_DEBUG, "available tracers:");
  Tracer *t;
  for (t = root_tracer_; t != nullptr; t = t->next_tracer_) {
    gpr_log(GPR_DEBUG, "\t%s", t->name_);
  }
}

bool Tracer::Set(const char *name, bool enabled) {
  Tracer *t;
  if (0 == strcmp(name, "all")) {
    for (t = root_tracer_; t; t = t->next_tracer_) {
      t->set_enabled(enabled);
    }
  } else if (0 == strcmp(name, "list_tracers")) {
    List();
  } else if (0 == strcmp(name, "refcount")) {
    for (t = root_tracer_; t; t = t->next_tracer_) {
      if (strstr(t->name_, "refcount") != NULL) {
        t->set_enabled(enabled);
      }
    }
  } else {
    bool found = false;
    for (t = root_tracer_; t; t = t->next_tracer_) {
      if (0 == strcmp(name, t->name_)) {
        t->set_enabled(enabled);
        found = true;
      }
    }
    if (!found) {
      gpr_log(GPR_ERROR, "Unknown trace var: '%s'", name);
      return false; /* early return */
    }
  }
  return true;
}

}  // namespace grpc_core

static void add(const char *beg, const char *end, char ***ss, size_t *ns) {
  size_t n = *ns;
  size_t np = n + 1;
  char *s;
  size_t len;
  GPR_ASSERT(end >= beg);
  len = (size_t)(end - beg);
  s = (char *)gpr_malloc(len + 1);
  memcpy(s, beg, len);
  s[len] = 0;
  *ss = (char **)gpr_realloc(*ss, sizeof(char **) * np);
  (*ss)[n] = s;
  *ns = np;
}

static void split(const char *s, char ***ss, size_t *ns) {
  const char *c = strchr(s, ',');
  if (c == NULL) {
    add(s, s + strlen(s), ss, ns);
  } else {
    add(s, c, ss, ns);
    split(c + 1, ss, ns);
  }
}

static void parse(const char *s) {
  char **strings = NULL;
  size_t nstrings = 0;
  size_t i;
  split(s, &strings, &nstrings);

  for (i = 0; i < nstrings; i++) {
    if (strings[i][0] == '-') {
      grpc_core::Tracer::Set(strings[i] + 1, false);
    } else {
      grpc_core::Tracer::Set(strings[i], true);
    }
  }

  for (i = 0; i < nstrings; i++) {
    gpr_free(strings[i]);
  }
  gpr_free(strings);
}

void grpc_tracer_init(const char *env_var) {
  char *e = gpr_getenv(env_var);
  if (e != NULL) {
    parse(e);
    gpr_free(e);
  }
}

void grpc_tracer_shutdown(void) {}

int grpc_tracer_set_enabled(const char *name, int enabled) {
  return grpc_core::Tracer::Set(name, enabled != 0);
}
