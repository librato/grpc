/*
 *
 * Copyright 2016, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef GRPC_CORE_LIB_SLICE_SLICE_INTERNAL_H
#define GRPC_CORE_LIB_SLICE_SLICE_INTERNAL_H

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>

#include "src/core/lib/iomgr/exec_ctx.h"

grpc_slice grpc_slice_ref_internal(grpc_slice slice);
void grpc_slice_unref_internal(grpc_exec_ctx *exec_ctx, grpc_slice slice);
void grpc_slice_buffer_reset_and_unref_internal(grpc_exec_ctx *exec_ctx,
                                                grpc_slice_buffer *sb);
void grpc_slice_buffer_destroy_internal(grpc_exec_ctx *exec_ctx,
                                        grpc_slice_buffer *sb);

void grpc_slice_intern_init(void);
void grpc_slice_intern_shutdown(void);
void grpc_test_only_set_slice_hash_seed(uint32_t key);
// if slice matches a static slice, consume it and replace it with the static
// slice, otherwise do nothing: this is a fast interning for well known strings
void grpc_slice_static_intern(grpc_slice *slice);
uint32_t grpc_static_slice_hash(void *refcnt, grpc_slice s);

#endif /* GRPC_CORE_LIB_SLICE_SLICE_INTERNAL_H */
