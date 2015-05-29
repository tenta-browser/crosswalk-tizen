/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "common/app_db.h"

#include <app_preference.h>
#include <memory>

#include "common/string_utils.h"

namespace wrt {

namespace {
  const char* kSectionPrefix = "_SECT_";
  const char* kSectionSuffix = "_SECT_";

}  // namespace

class PreferenceAppDB : public AppDB {
 public:
  PreferenceAppDB();
  virtual bool HasKey(const std::string& section,
                      const std::string& key) const;
  virtual std::string Get(const std::string& section,
                          const std::string& key) const;
  virtual void Set(const std::string& section,
                   const std::string& key,
                   const std::string& value);
  virtual void GetKeys(const std::string& section,
                       std::list<std::string>* keys) const;
  virtual void Remove(const std::string& section,
                      const std::string& key);
};

PreferenceAppDB::PreferenceAppDB() {
}

bool PreferenceAppDB::HasKey(const std::string& section,
                             const std::string& key) const {
  bool existed = false;
  std::string combined_key = kSectionPrefix + section + kSectionSuffix + key;
  return preference_is_existing(combined_key.c_str(), &existed) == 0 && existed;
}

std::string PreferenceAppDB::Get(const std::string& section,
                                 const std::string& key) const {
  std::string combined_key = kSectionPrefix + section + kSectionSuffix + key;
  char* value;
  if (preference_get_string(combined_key.c_str(), &value) == 0) {
    std::unique_ptr<char, decltype(std::free)*> ptr {value, std::free};
    return std::string(value);
  }
  return std::string();
}

void PreferenceAppDB::Set(const std::string& section,
                          const std::string& key,
                          const std::string& value) {
  std::string combined_key = kSectionPrefix + section + kSectionSuffix + key;
  preference_set_string(combined_key.c_str(), value.c_str());
}

void PreferenceAppDB::GetKeys(const std::string& section,
                              std::list<std::string>* keys) const {
  auto callback = [](const char* key, void *user_data) {
    auto list = static_cast<std::list<std::string>*>(user_data);
    if (utils::StartsWith(key, list->front())) {
      list->push_back(key+list->front().size());
    }
    return true;
  };
  std::string key_prefix = kSectionPrefix + section + kSectionSuffix;
  keys->push_front(key_prefix);
  preference_foreach_item(callback, keys);
  keys->pop_front();
}

void PreferenceAppDB::Remove(const std::string& section,
                             const std::string& key) {
  std::string combined_key = kSectionPrefix + section + kSectionSuffix + key;
  preference_remove(combined_key.c_str());
}


AppDB* AppDB::GetInstance() {
  static PreferenceAppDB instance;
  return &instance;
}



}  // namespace wrt
