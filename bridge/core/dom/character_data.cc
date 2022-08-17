/*
 * Copyright (C) 2019-2022 The Kraken authors. All rights reserved.
 * Copyright (C) 2022-present The WebF authors. All rights reserved.
 */

#include "character_data.h"
#include "core/dom/document.h"

namespace webf {

void CharacterData::setData(const AtomicString& data) {
  data_ = data;
}

std::string CharacterData::nodeValue() const {
  return data_.ToStdString();
}
CharacterData::CharacterData(TreeScope& tree_scope, const AtomicString& text, Node::ConstructionType type)
    : Node(tree_scope.GetDocument().GetExecutingContext(), &tree_scope, type),
      data_(!text.IsNull() ? text : AtomicString::Empty(ctx())) {
  assert(type == kCreateOther || type == kCreateText);
}

}  // namespace webf