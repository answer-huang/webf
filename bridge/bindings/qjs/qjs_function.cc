/*
 * Copyright (C) 2021 Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */

#include "qjs_function.h"
#include <algorithm>

namespace kraken {

bool QJSFunction::IsFunction(JSContext* ctx) {
  return JS_IsFunction(ctx, function_);
}

ScriptValue QJSFunction::Invoke(JSContext* ctx, int32_t argc, ScriptValue* arguments) {
  // 'm_function' might be destroyed when calling itself (if it frees the handler), so must take extra care.
  JS_DupValue(ctx, function_);

  JSValue argv[std::max(1, argc)];

  for (int i = 0; i < argc; i++) {
    argv[0 + i] = arguments[i].ToQuickJS();
  }

  JSValue returnValue = JS_Call(ctx, function_, JS_UNDEFINED, argc, argv);

  // Free the previous duplicated function.
  JS_FreeValue(ctx, function_);

  return ScriptValue(ctx, returnValue);
}

void QJSFunction::Trace(GCVisitor* visitor) const {
  visitor->Trace(function_);
}

void QJSFunction::Dispose() const {
  JS_FreeValueRT(JS_GetRuntime(ctx_), function_);
}
}  // namespace kraken