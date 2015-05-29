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

#ifndef WRT_COMMON_APP_CONTROL_H_
#define WRT_COMMON_APP_CONTROL_H_

#include <app_control.h>
#include <bundle.h>
#include <string>
#include <vector>
#include <map>

namespace wrt {

class AppControl {
 public:
  explicit AppControl(app_control_h app_control);
  AppControl();
  ~AppControl();
  // disable copy
  AppControl(const AppControl& src) = delete;
  AppControl& operator=(const AppControl&) = delete;

  std::string operation() const;
  void set_operation(const std::string& operation);
  std::string mime() const;
  void set_mime(const std::string& mime);
  std::string uri() const;
  void set_uri(const std::string& uri);
  std::string category() const;
  void set_category(const std::string& category);
  std::string data(const std::string& key) const;
  std::vector<std::string> data_array(const std::string& key) const;
  std::string encoded_bundle();

  bool IsDataArray(const std::string& key);
  bool AddData(const std::string& key, const std::string& value);
  bool AddDataArray(const std::string& key,
                    const std::vector<std::string>& value_array);
  bool Reply(const std::map<std::string, std::vector<std::string>>& data);
  bool LaunchRequest();

 private:
  app_control_h app_control_;
  bundle* app_control_bundle_;
};

}  // namespace wrt

#endif  // WRT_COMMON_APP_CONTROL_H_
