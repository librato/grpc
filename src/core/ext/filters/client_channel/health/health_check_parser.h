/*
 *
 * Copyright 2019 gRPC authors.
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

#ifndef GRPC_CORE_EXT_FILTERS_CLIENT_CHANNEL_HEALTH_HEALTH_CHECK_PARSER_H
#define GRPC_CORE_EXT_FILTERS_CLIENT_CHANNEL_HEALTH_HEALTH_CHECK_PARSER_H

#include <grpc/support/port_platform.h>

#include "src/core/ext/filters/client_channel/service_config.h"

namespace grpc_core {

class HealthCheckParsedObject : public ServiceConfigParsedObject {
 public:
  HealthCheckParsedObject(const char* service_name)
      : service_name_(service_name) {}

  const char* service_name() const { return service_name_; }

 private:
  const char* service_name_;
};

class HealthCheckParser : public ServiceConfigParser {
 public:
  UniquePtr<ServiceConfigParsedObject> ParseGlobalParams(
      const grpc_json* json, grpc_error** error) override;

  static void Register();

  static size_t ParserIndex();
};
}  // namespace grpc_core
#endif /* GRPC_CORE_EXT_FILTERS_CLIENT_CHANNEL_HEALTH_HEALTH_CHECK_PARSER_H */
