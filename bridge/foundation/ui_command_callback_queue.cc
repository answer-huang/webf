/*
 * Copyright (C) 2020-present The Kraken authors. All rights reserved.
 */

#include "webf_bridge.h"

namespace foundation {

UICommandCallbackQueue* UICommandCallbackQueue::instance() {
  static UICommandCallbackQueue* queue = nullptr;

  if (queue == nullptr) {
    queue = new UICommandCallbackQueue();
  }

  return queue;
}

void UICommandCallbackQueue::flushCallbacks() {
  for (auto& item : queue) {
    item.callback(item.data);
  }
  queue.clear();
}

void UICommandCallbackQueue::registerCallback(const Callback& callback, void* data) {
  CallbackItem item{callback, data};
  queue.emplace_back(item);
}

}  // namespace foundation
