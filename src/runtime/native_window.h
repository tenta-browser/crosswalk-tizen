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

#ifndef WRT_RUNTIME_NATIVE_WINDOW_H_
#define WRT_RUNTIME_NATIVE_WINDOW_H_
#include <functional>
#include <map>

#include <Elementary.h>

namespace wrt {

class NativeWindow {
 public:
  typedef std::function<void(int)> RotationHandler;
  NativeWindow();
  virtual ~NativeWindow();

  void Initialize();

  bool initialized() const { return initialized_; }
  Evas_Object* evas_object() const;
  void SetContent(Evas_Object* content);
  void SetRotationLock(int degree);
  void SetAutoRotation();
  int AddRotationHandler(RotationHandler handler);
  void RemoveRotationHandler(int id);
  int rotation() const { return rotation_; }
  void Show();
  void Active();
  void InActive();
  void FullScreen(bool enable);

 protected:
  virtual Evas_Object* CreateWindowInternal() = 0;

 private:
  static void DidDeleteRequested(void* data, Evas_Object* obj,
                                 void* event_info);
  static void DidProfileChanged(void* data, Evas_Object* obj, void* event_info);
  void DidRotation(int degree);
  void DidFocusChanged(bool got);


  bool initialized_;
  Evas_Object* window_;
  Evas_Object* focus_;
  Evas_Object* content_;
  int rotation_;
  int handler_id_;
  std::map<int, RotationHandler> handler_table_;
};

}  // namespace wrt


#endif  // WRT_RUNTIME_NATIVE_WINDOW_H_
