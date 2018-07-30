/*
 *
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
 *
 */

#include <grpc/impl/codegen/port_platform.h>

#include "src/core/lib/channel/channelz.h"

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/string_util.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/core/lib/channel/channelz_registry.h"
#include "src/core/lib/channel/status_util.h"
#include "src/core/lib/gpr/string.h"
#include "src/core/lib/gpr/useful.h"
#include "src/core/lib/gprpp/memory.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/surface/channel.h"
#include "src/core/lib/transport/error_utils.h"

namespace grpc_core {
namespace channelz {

BaseNode::BaseNode(EntityType type)
    : type_(type), uuid_(ChannelzRegistry::Register(this)) {}

BaseNode::~BaseNode() { ChannelzRegistry::Unregister(uuid_); }

char* BaseNode::RenderJsonString() {
  grpc_json* json = RenderJson();
  char* json_str = grpc_json_dump_to_string(json, 0);
  grpc_json_destroy(json);
  return json_str;
}

CallCountingHelper::CallCountingHelper() {
  gpr_atm_no_barrier_store(&last_call_started_millis_,
                           (gpr_atm)ExecCtx::Get()->Now());
}

CallCountingHelper::~CallCountingHelper() {}

void CallCountingHelper::RecordCallStarted() {
  gpr_atm_no_barrier_fetch_add(&calls_started_, (gpr_atm)1);
  gpr_atm_no_barrier_store(&last_call_started_millis_,
                           (gpr_atm)ExecCtx::Get()->Now());
}

void CallCountingHelper::PopulateCallData(grpc_json* json) {
  grpc_json* json_iterator = nullptr;
  if (calls_started_ != 0) {
    json_iterator = grpc_json_add_number_string_child(
        json, json_iterator, "callsStarted", calls_started_);
  }
  if (calls_succeeded_ != 0) {
    json_iterator = grpc_json_add_number_string_child(
        json, json_iterator, "callsSucceeded", calls_succeeded_);
  }
  if (calls_failed_) {
    json_iterator = grpc_json_add_number_string_child(
        json, json_iterator, "callsFailed", calls_failed_);
  }
  gpr_timespec ts =
      grpc_millis_to_timespec(last_call_started_millis_, GPR_CLOCK_REALTIME);
  json_iterator =
      grpc_json_create_child(json_iterator, json, "lastCallStartedTimestamp",
                             gpr_format_timespec(ts), GRPC_JSON_STRING, true);
}

ChannelNode::ChannelNode(grpc_channel* channel, size_t channel_tracer_max_nodes,
                         bool is_top_level_channel)
    : BaseNode(is_top_level_channel ? EntityType::kTopLevelChannel
                                    : EntityType::kInternalChannel),
      channel_(channel),
      target_(UniquePtr<char>(grpc_channel_get_target(channel_))) {
  trace_.Init(channel_tracer_max_nodes);
}

ChannelNode::~ChannelNode() { trace_.Destroy(); }

grpc_json* ChannelNode::RenderJson() {
  // We need to track these three json objects to build our object
  grpc_json* top_level_json = grpc_json_create(GRPC_JSON_OBJECT);
  grpc_json* json = top_level_json;
  grpc_json* json_iterator = nullptr;
  // create and fill the ref child
  json_iterator = grpc_json_create_child(json_iterator, json, "ref", nullptr,
                                         GRPC_JSON_OBJECT, false);
  json = json_iterator;
  json_iterator = nullptr;
  json_iterator = grpc_json_add_number_string_child(json, json_iterator,
                                                    "channelId", uuid());
  // reset json iterators to top level object
  json = top_level_json;
  json_iterator = nullptr;
  // create and fill the data child.
  grpc_json* data = grpc_json_create_child(json_iterator, json, "data", nullptr,
                                           GRPC_JSON_OBJECT, false);
  json = data;
  json_iterator = nullptr;
  // populate the target.
  GPR_ASSERT(target_.get() != nullptr);
  grpc_json_create_child(nullptr, json, "target", target_.get(),
                         GRPC_JSON_STRING, false);
  // fill in the channel trace if applicable
  grpc_json* trace_json = trace_->RenderJson();
  if (trace_json != nullptr) {
    trace_json->key = "trace";  // this object is named trace in channelz.proto
    grpc_json_link_child(json, trace_json, nullptr);
  }
  // ask CallCountingHelper to populate trace and call count data.
  call_counter_.PopulateCallData(json);
  return top_level_json;
}

RefCountedPtr<ChannelNode> ChannelNode::MakeChannelNode(
    grpc_channel* channel, size_t channel_tracer_max_nodes,
    bool is_top_level_channel) {
  return MakeRefCounted<grpc_core::channelz::ChannelNode>(
      channel, channel_tracer_max_nodes, is_top_level_channel);
}

}  // namespace channelz
}  // namespace grpc_core
