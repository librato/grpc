# Copyright 2016, Google Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#
# This is for the gRPC build system. This isn't intended to be used outsite of
# the BUILD file for gRPC. It contains the mapping for the template system we
# use to generate other platform's build system files.
#

def grpc_cc_library(name, srcs = [], public_hdrs = [], hdrs = [], external_deps = [], deps = [], standalone = False, language = "C++"):
  copts = []
  if language.upper() == "C":
    copts = ["-std=c99"]
  native.cc_library(
    name = name,
    srcs = srcs,
    hdrs = hdrs + public_hdrs,
    deps = deps + ["//external:" + dep for dep in external_deps],
    copts = copts,
    linkopts = ["-pthread"],
    includes = [
        "include"
    ]
  )

def grpc_proto_plugin(name, srcs = [], deps = []):
  native.cc_binary(
    name = name,
    srcs = srcs,
    deps = deps,
  )

load("//:bazel/cc_grpc_library.bzl", "cc_grpc_library")

def grpc_proto_library(name, srcs = [], deps = [], well_known_deps = [], has_services = True, use_external = False):
  cc_grpc_library(
    name = name,
    srcs = srcs,
    deps = deps,
    proto_only = not has_services,
    use_external = use_external,
  )

