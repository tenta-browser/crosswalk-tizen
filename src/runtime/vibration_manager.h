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

#ifndef WRT_RUNTIME_VIBRATION_MANAGER_H_
#define WRT_RUNTIME_VIBRATION_MANAGER_H_

// TODO(sngn.lee): this class will move to src/platform/ directory
namespace wrt {
namespace platform {
class VibrationManager {
 public:
  static VibrationManager* GetInstance();
  virtual void Start(int ms) = 0;
  virtual void Stop() = 0;
};
}  // namespace platform
}  // namespace wrt

#endif  // WRT_RUNTIME_VIBRATION_MANAGER_H_
