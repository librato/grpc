//
// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <grpc/support/port_platform.h>

#include "src/core/ext/filters/client_channel/service_config.h"

#include <string.h>

#include <grpc/impl/codegen/grpc_types.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/string_util.h>

#include "src/core/lib/gpr/string.h"
#include "src/core/lib/json/json.h"
#include "src/core/lib/slice/slice_hash_table.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_string_helpers.h"

namespace grpc_core {

int ServiceConfig::registered_parsers_count = 0;
UniquePtr<ServiceConfigParser>
    ServiceConfig::registered_parsers[ServiceConfigParser::kMaxParsers];

RefCountedPtr<ServiceConfig> ServiceConfig::Create(const char* json) {
  UniquePtr<char> service_config_json(gpr_strdup(json));
  UniquePtr<char> json_string(gpr_strdup(json));
  grpc_json* json_tree = grpc_json_parse_string(json_string.get());
  if (json_tree == nullptr) {
    gpr_log(GPR_INFO, "failed to parse JSON for service config");
    return nullptr;
  }
  bool success;
  auto return_value = MakeRefCounted<ServiceConfig>(
      std::move(service_config_json), std::move(json_string), json_tree,
      &success);

  // return return_value;
  return success ? return_value : nullptr;
}

ServiceConfig::ServiceConfig(UniquePtr<char> service_config_json,
                             UniquePtr<char> json_string, grpc_json* json_tree,
                             bool* success)
    : service_config_json_(std::move(service_config_json)),
      json_string_(std::move(json_string)),
      json_tree_(json_tree) {
  GPR_DEBUG_ASSERT(success != nullptr);
  if (json_tree->type != GRPC_JSON_OBJECT || json_tree->key != nullptr) {
    gpr_log(GPR_ERROR, "error");
    *success = false;
    return;
  }
  ParseGlobalParams(json_tree, success);
  if (!*success) {
    gpr_log(GPR_ERROR, "global error");
    return;
  }
  ParsePerMethodParams(json_tree, success);
  if (!*success) {
    gpr_log(GPR_ERROR, "local error");
    return;
  }
}

void ServiceConfig::ParseGlobalParams(const grpc_json* json_tree,
                                      bool* success) {
  GPR_DEBUG_ASSERT(success != nullptr);
  GPR_DEBUG_ASSERT(json_tree_->type == GRPC_JSON_OBJECT);
  GPR_DEBUG_ASSERT(json_tree_->key == nullptr);
  for (auto i = 0; i < registered_parsers_count; i++) {
    auto parsed_obj =
        registered_parsers[i]->ParseGlobalParams(json_tree, success);
    if (!*success) {
      return;
    }
    parsed_global_service_config_objects.push_back(parsed_obj);
  }
  *success = true;
}

bool ServiceConfig::ParseJsonMethodConfigToServiceConfigObjectsTable(
    const grpc_json* json,
    SliceHashTable<RefCountedPtr<ServiceConfigObjectsVector>>::Entry* entries,
    size_t* idx) {
  auto objs_vector = MakeRefCounted<ServiceConfigObjectsVector>();
  for (auto i = 0; i < registered_parsers_count; i++) {
    bool success;
    auto parsed_obj =
        registered_parsers[i]->ParsePerMethodParams(json, &success);
    if (!success) {
      return false;
    }
    objs_vector->vector.push_back(parsed_obj);
  }
  // Construct list of paths.
  InlinedVector<UniquePtr<char>, 10> paths;
  for (grpc_json* child = json->child; child != nullptr; child = child->next) {
    if (child->key == nullptr) continue;
    if (strcmp(child->key, "name") == 0) {
      if (child->type != GRPC_JSON_ARRAY) return false;
      for (grpc_json* name = child->child; name != nullptr; name = name->next) {
        UniquePtr<char> path = ParseJsonMethodName(name);
        if (path == nullptr) return false;
        paths.push_back(std::move(path));
      }
    }
  }
  if (paths.size() == 0) return false;  // No names specified.
  // Add entry for each path.
  for (size_t i = 0; i < paths.size(); ++i) {
    entries[*idx].key = grpc_slice_from_copied_string(paths[i].get());
    entries[*idx].value = objs_vector;  // Takes a new ref.
    ++*idx;
  }
  return true;
}

void ServiceConfig::ParsePerMethodParams(const grpc_json* json_tree,
                                         bool* success) {
  GPR_DEBUG_ASSERT(success != nullptr);
  GPR_DEBUG_ASSERT(json_tree_->type == GRPC_JSON_OBJECT);
  GPR_DEBUG_ASSERT(json_tree_->key == nullptr);
  SliceHashTable<RefCountedPtr<ServiceConfigObjectsVector>>::Entry* entries =
      nullptr;
  size_t num_entries = 0;
  for (grpc_json* field = json_tree->child; field != nullptr;
       field = field->next) {
    if (field->key == nullptr) {
      *success = false;
      return;
    }
    if (strcmp(field->key, "methodConfig") == 0) {
      if (entries != nullptr) {
        GPR_ASSERT(false);
      }
      if (field->type != GRPC_JSON_ARRAY) {
        *success = false;
        return;
      }
      for (grpc_json* method = field->child; method != nullptr;
           method = method->next) {
        int count = CountNamesInMethodConfig(method);
        if (count <= 0) {
          *success = false;
          return;
        }
        num_entries += static_cast<size_t>(count);
      }
      entries = static_cast<
          SliceHashTable<RefCountedPtr<ServiceConfigObjectsVector>>::Entry*>(
          gpr_zalloc(
              num_entries *
              sizeof(SliceHashTable<
                     RefCountedPtr<ServiceConfigObjectsVector>>::Entry)));
      size_t idx = 0;
      for (grpc_json* method = field->child; method != nullptr;
           method = method->next) {
        if (!ParseJsonMethodConfigToServiceConfigObjectsTable(method, entries,
                                                              &idx)) {
          for (size_t i = 0; i < idx; ++i) {
            grpc_slice_unref_internal(entries[i].key);
            entries[i].value.reset();
          }
          gpr_free(entries);
          *success = false;
          return;
        }
      }
      GPR_DEBUG_ASSERT(idx == num_entries);
      break;
    }
  }
  if (entries != nullptr) {
    parsed_method_service_config_objects_table =
        SliceHashTable<RefCountedPtr<ServiceConfigObjectsVector>>::Create(
            num_entries, entries, nullptr);
    gpr_free(entries);
  }
  *success = true;
}

ServiceConfig::~ServiceConfig() { grpc_json_destroy(json_tree_); }

const char* ServiceConfig::GetLoadBalancingPolicyName() const {
  if (json_tree_->type != GRPC_JSON_OBJECT || json_tree_->key != nullptr) {
    return nullptr;
  }
  const char* lb_policy_name = nullptr;
  for (grpc_json* field = json_tree_->child; field != nullptr;
       field = field->next) {
    if (field->key == nullptr) return nullptr;
    if (strcmp(field->key, "loadBalancingPolicy") == 0) {
      if (lb_policy_name != nullptr) return nullptr;  // Duplicate.
      if (field->type != GRPC_JSON_STRING) return nullptr;
      lb_policy_name = field->value;
    }
  }
  return lb_policy_name;
}

int ServiceConfig::CountNamesInMethodConfig(grpc_json* json) {
  int num_names = 0;
  for (grpc_json* field = json->child; field != nullptr; field = field->next) {
    if (field->key != nullptr && strcmp(field->key, "name") == 0) {
      if (field->type != GRPC_JSON_ARRAY) return -1;
      for (grpc_json* name = field->child; name != nullptr; name = name->next) {
        if (name->type != GRPC_JSON_OBJECT) return -1;
        ++num_names;
      }
    }
  }
  return num_names;
}

UniquePtr<char> ServiceConfig::ParseJsonMethodName(grpc_json* json) {
  if (json->type != GRPC_JSON_OBJECT) return nullptr;
  const char* service_name = nullptr;
  const char* method_name = nullptr;
  for (grpc_json* child = json->child; child != nullptr; child = child->next) {
    if (child->key == nullptr) return nullptr;
    if (child->type != GRPC_JSON_STRING) return nullptr;
    if (strcmp(child->key, "service") == 0) {
      if (service_name != nullptr) return nullptr;  // Duplicate.
      if (child->value == nullptr) return nullptr;
      service_name = child->value;
    } else if (strcmp(child->key, "method") == 0) {
      if (method_name != nullptr) return nullptr;  // Duplicate.
      if (child->value == nullptr) return nullptr;
      method_name = child->value;
    }
  }
  if (service_name == nullptr) return nullptr;  // Required field.
  char* path;
  gpr_asprintf(&path, "/%s/%s", service_name,
               method_name == nullptr ? "*" : method_name);
  return UniquePtr<char>(path);
}

}  // namespace grpc_core
