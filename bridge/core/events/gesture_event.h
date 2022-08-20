/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */

#ifndef BRIDGE_CORE_EVENTS_GESTURE_EVENT_H_
#define BRIDGE_CORE_EVENTS_GESTURE_EVENT_H_

#include "bindings/qjs/dictionary_base.h"
#include "bindings/qjs/source_location.h"
#include "core/dom/events/event.h"
#include "qjs_gesture_event_init.h"

namespace webf {

class GestureEvent : public Event {
  DEFINE_WRAPPERTYPEINFO();

 public:
  using ImplType = GestureEvent*;

  static GestureEvent* Create(ExecutingContext* context, const AtomicString& type, ExceptionState& exception_state);

  static GestureEvent* Create(ExecutingContext* context,
                              const AtomicString& type,
                              const std::shared_ptr<GestureEventInit>& initializer,
                              ExceptionState& exception_state);

  explicit GestureEvent(ExecutingContext* context, const AtomicString& type, ExceptionState& exception_state);

  explicit GestureEvent(ExecutingContext* context,
                        const AtomicString& type,
                        const std::shared_ptr<GestureEventInit>& initializer,
                        ExceptionState& exception_state);

  const AtomicString& state() const;
  const AtomicString& direction() const;
  double deltaX() const;
  double deltaY() const;
  double velocityX() const;
  double velocityY() const;
  double scale() const;
  double rotation() const;

 private:
  AtomicString state_;
  AtomicString direction_;
  double deltaX_;
  double deltaY_;
  double velocityX_;
  double velocityY_;
  double scale_;
  double rotation_;
};

}  // namespace webf

#endif  // BRIDGE_CORE_EVENTS_GESTURE_EVENT_H_
