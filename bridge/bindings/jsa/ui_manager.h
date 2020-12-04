/*
 * Copyright (C) 2020 Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */

#ifndef KRAKENBRIDGE_UI_MANAGER_H
#define KRAKENBRIDGE_UI_MANAGER_H

#include "foundation/js_engine_adaptor.h"

namespace kraken::binding::jsa {
void bindUIManager(KRAKEN_JS_CONTEXT &context);
} // namespace kraken

#endif // KRAKENBRIDGE_UI_MANAGER_H