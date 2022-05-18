/*
 * Copyright (C) 2021-present The Kraken authors. All rights reserved.
 */

#include "core/dom/legacy/bounding_client_rect.h"
#include "gtest/gtest.h"
#include "kraken_test_env.h"
using namespace kraken;

TEST(Element, setAttribute) {
  bool static errorCalled = false;
  bool static logCalled = false;
  kraken::KrakenPage::consoleMessageHandler = [](void* ctx, const std::string& message, int logLevel) {
    logCalled = true;
    EXPECT_STREQ(message.c_str(), "1234");
  };
  auto bridge = TEST_init([](int32_t contextId, const char* errmsg) {
    KRAKEN_LOG(VERBOSE) << errmsg;
    errorCalled = true;
  });
  auto context = bridge->GetExecutingContext();
  const char* code =
      "let div = document.createElement('div');"
      "div.setAttribute('hello', 1234);"
      "document.body.appendChild(div);"
      "console.log(div.getAttribute('hello'))";
  bridge->evaluateScript(code, strlen(code), "vm://", 0);
  EXPECT_EQ(errorCalled, false);
  EXPECT_EQ(logCalled, true);
}

TEST(Element, getAttribute) {
  bool static errorCalled = false;
  bool static logCalled = false;
  kraken::KrakenPage::consoleMessageHandler = [](void* ctx, const std::string& message, int logLevel) {
    logCalled = true;
    EXPECT_STREQ(message.c_str(), "helloworld");
  };
  auto bridge = TEST_init([](int32_t contextId, const char* errmsg) {
    KRAKEN_LOG(VERBOSE) << errmsg;
    errorCalled = true;
  });
  auto context = bridge->GetExecutingContext();
  const char* code =
      "let div = document.createElement('div');"
      "let string = 'helloworld';"
      "let string2 = 'helloworld';"
      "div.setAttribute('hello', '456');"
      "div.setAttribute('hello', string);"
      "let otherDiv = div.cloneNode(true);"
      "otherDiv.setAttribute('hello', string2);"
      "document.body.appendChild(div);"
      "console.log(div.getAttribute('hello'));"
      "console.log(otherDiv.getAttribute('hello'));";
  bridge->evaluateScript(code, strlen(code), "vm://", 0);
  EXPECT_EQ(errorCalled, false);
  EXPECT_EQ(logCalled, true);
}

TEST(Element, setAttributeWithHTML) {
  bool static errorCalled = false;
  bool static logCalled = false;
  kraken::KrakenPage::consoleMessageHandler = [](void* ctx, const std::string& message, int logLevel) {
    logCalled = true;
    EXPECT_STREQ(message.c_str(), "100%");
  };
  auto bridge = TEST_init([](int32_t contextId, const char* errmsg) {
    KRAKEN_LOG(VERBOSE) << errmsg;
    errorCalled = true;
  });
  auto context = bridge->GetExecutingContext();
  const char* code =
      "let div = document.createElement('div');"
      "div.innerHTML = '<img src=\"https://miniapp-nikestore-demo.oss-cn-beijing.aliyuncs.com/white_shoes_v1.png\" "
      "style=\"width:100%;height:auto;\">';"
      "console.log(div.firstChild.style.width);";
  bridge->evaluateScript(code, strlen(code), "vm://", 0);
  EXPECT_EQ(errorCalled, false);
}

TEST(Element, instanceofNode) {
  bool static errorCalled = false;
  bool static logCalled = false;
  kraken::KrakenPage::consoleMessageHandler = [](void* ctx, const std::string& message, int logLevel) {
    logCalled = true;
    EXPECT_STREQ(message.c_str(), "true");
  };
  auto bridge = TEST_init([](int32_t contextId, const char* errmsg) {
    KRAKEN_LOG(VERBOSE) << errmsg;
    errorCalled = true;
  });
  auto context = bridge->GetExecutingContext();
  const char* code =
      "let div = document.createElement('div');"
      "console.log(div instanceof Node)";
  bridge->evaluateScript(code, strlen(code), "vm://", 0);

  EXPECT_EQ(errorCalled, false);
  EXPECT_EQ(logCalled, true);
}

TEST(Element, instanceofEventTarget) {
  bool static errorCalled = false;
  bool static logCalled = false;
  kraken::KrakenPage::consoleMessageHandler = [](void* ctx, const std::string& message, int logLevel) {
    logCalled = true;
    EXPECT_STREQ(message.c_str(), "true");
  };
  auto bridge = TEST_init([](int32_t contextId, const char* errmsg) {
    KRAKEN_LOG(VERBOSE) << errmsg;
    errorCalled = true;
  });
  auto context = bridge->GetExecutingContext();
  const char* code =
      "let div = document.createElement('div');"
      "console.log(div instanceof EventTarget)";
  bridge->evaluateScript(code, strlen(code), "vm://", 0);

  EXPECT_EQ(errorCalled, false);
  EXPECT_EQ(logCalled, true);
}

TEST(Element, stringifyBoundingClientRect) {
  using namespace kraken;

  bool static errorCalled = false;
  bool static logCalled = false;
  kraken::KrakenPage::consoleMessageHandler = [](void* ctx, const std::string& message, int logLevel) {
    logCalled = true;
    EXPECT_STREQ(message.c_str(),
                 "{\"x\":10,\"y\":20,\"width\":30,\"height\":40,\"top\":10,\"right\":20,\"bottom\":30,\"left\":40}");
  };
  auto bridge = TEST_init([](int32_t contextId, const char* errmsg) {
    KRAKEN_LOG(VERBOSE) << errmsg;
    errorCalled = true;
  });
  auto context = bridge->GetExecutingContext();

  NativeBoundingClientRect nativeRect{
      10.0, 20.0, 30.0, 40.0, 10.0, 20.0, 30.0, 40.0,
  };

  {
    MemberMutationScope scope{context};
    auto* clientRect = BoundingClientRect::Create(context, &nativeRect);
    context->DefineGlobalProperty("boundingClient", clientRect->ToQuickJS());
  }

  const char* code = "console.log(JSON.stringify(boundingClient))";
  bridge->evaluateScript(code, strlen(code), "vm://", 0);

  EXPECT_EQ(errorCalled, false);
  EXPECT_EQ(logCalled, true);
}