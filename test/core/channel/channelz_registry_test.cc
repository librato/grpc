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

#include <stdlib.h>
#include <string.h>

#include <grpc/grpc.h>
#include <gtest/gtest.h>

#include <grpc/support/alloc.h>
#include <grpc/support/log.h>

#include "src/core/lib/channel/channel_trace.h"
#include "src/core/lib/channel/channelz.h"
#include "src/core/lib/channel/channelz_registry.h"
#include "src/core/lib/gpr/useful.h"
#include "src/core/lib/gprpp/memory.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/json/json.h"
#include "src/core/lib/surface/channel.h"

#include "test/core/util/test_config.h"

#include <stdlib.h>
#include <string.h>

namespace grpc_core {
namespace channelz {
namespace testing {
namespace {

class ChannelFixture {
 public:
  ChannelFixture() {
    grpc_arg client_a[1];
    client_a[0].type = GRPC_ARG_INTEGER;
    client_a[0].key = const_cast<char*>(GRPC_ARG_ENABLE_CHANNELZ);
    client_a[0].value.integer = true;
    grpc_channel_args client_args = {GPR_ARRAY_SIZE(client_a), client_a};
    channel_ =
        grpc_insecure_channel_create("fake_target", &client_args, nullptr);
  }

  ~ChannelFixture() { grpc_channel_destroy(channel_); }

  grpc_channel* channel() { return channel_; }

 private:
  grpc_channel* channel_;
};

}  // namespace

// Tests basic ChannelTrace functionality like construction, adding trace, and
// lookups by uuid.
TEST(ChannelzRegistryTest, UuidStartsAboveZeroTest) {
  ChannelFixture channel;
  ChannelNode* channelz_channel =
      grpc_channel_get_channelz_node(channel.channel());
  intptr_t uuid = ChannelzRegistry::RegisterChannelNode(channelz_channel);
  EXPECT_GT(uuid, 0) << "First uuid chose must be greater than zero. Zero if "
                        "reserved according to "
                        "https://github.com/grpc/proposal/blob/master/"
                        "A14-channelz.md";
  ChannelzRegistry::UnregisterChannelNode(uuid);
}

TEST(ChannelzRegistryTest, UuidsAreIncreasing) {
  ChannelFixture channel;
  ChannelNode* channelz_channel =
      grpc_channel_get_channelz_node(channel.channel());
  std::vector<intptr_t> uuids;
  uuids.reserve(10);
  for (int i = 0; i < 10; ++i) {
    // reregister the same object. It's ok since we are just testing uuids
    uuids.push_back(ChannelzRegistry::RegisterChannelNode(channelz_channel));
  }
  for (size_t i = 1; i < uuids.size(); ++i) {
    EXPECT_LT(uuids[i - 1], uuids[i]) << "Uuids must always be increasing";
  }
}

TEST(ChannelzRegistryTest, RegisterGetTest) {
  ChannelFixture channel;
  ChannelNode* channelz_channel =
      grpc_channel_get_channelz_node(channel.channel());
  intptr_t uuid = ChannelzRegistry::RegisterChannelNode(channelz_channel);
  ChannelNode* retrieved = ChannelzRegistry::GetChannelNode(uuid);
  EXPECT_EQ(channelz_channel, retrieved);
}

TEST(ChannelzRegistryTest, RegisterManyItems) {
  ChannelFixture channel;
  ChannelNode* channelz_channel =
      grpc_channel_get_channelz_node(channel.channel());
  for (int i = 0; i < 100; i++) {
    intptr_t uuid = ChannelzRegistry::RegisterChannelNode(channelz_channel);
    ChannelNode* retrieved = ChannelzRegistry::GetChannelNode(uuid);
    EXPECT_EQ(channelz_channel, retrieved);
  }
}

TEST(ChannelzRegistryTest, NullIfNotPresentTest) {
  ChannelFixture channel;
  ChannelNode* channelz_channel =
      grpc_channel_get_channelz_node(channel.channel());
  intptr_t uuid = ChannelzRegistry::RegisterChannelNode(channelz_channel);
  // try to pull out a uuid that does not exist.
  ChannelNode* nonexistant = ChannelzRegistry::GetChannelNode(uuid + 1);
  EXPECT_EQ(nonexistant, nullptr);
  ChannelNode* retrieved = ChannelzRegistry::GetChannelNode(uuid);
  EXPECT_EQ(channelz_channel, retrieved);
}

}  // namespace testing
}  // namespace channelz
}  // namespace grpc_core

int main(int argc, char** argv) {
  grpc_test_init(argc, argv);
  grpc_init();
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
