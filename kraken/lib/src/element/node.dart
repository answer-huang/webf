/*
 * Copyright (C) 2019-present Alibaba Inc. All rights reserved.
 * Author: Kraken Team.
 */
import 'package:flutter/rendering.dart';
import 'package:kraken/element.dart';
import 'package:kraken/rendering.dart';
import 'package:kraken/style.dart';
import 'package:meta/meta.dart';

const String DATA = 'data';

enum NodeType {
  ELEMENT_NODE,
  TEXT_NODE,
  COMMENT_NODE,
  DOCUMENT_NODE,
  DOCUMENT_FRAGMENT_NODE,
}

class Comment extends Node {
  Comment(int nodeId, this.data) : super(NodeType.COMMENT_NODE, nodeId, '#comment');

  // The comment information.
  String data;
}

class TextNode extends Node with NodeLifeCycle, TextStyleMixin {
  TextNode(int nodeId, this._data) : super(NodeType.TEXT_NODE, nodeId, '#text') {
    // Update text after connected.
    queueAfterConnected(_onTextNodeConnected);
  }

  RenderTextBox renderTextBox;

  void _onTextNodeConnected() {
    Element parentElement = parentNode;
    renderTextBox = RenderTextBox(
      nodeId: nodeId,
      text: data,
      // inherit parent style
      style: parentElement.style,
    );
    parentElement.renderLayoutElement.add(renderTextBox);
  }

  // The text string.
  String _data;
  String get data => _data;
  set data(String newData) {
    assert(newData != null);
    _data = newData;
    updateTextStyle();
  }

  void updateTextStyle() {
    if (isConnected) {
      _doUpdateTextStyle();
    } else {
      queueAfterConnected(_doUpdateTextStyle);
    }
  }

  void _doUpdateTextStyle() {
    // parentNode must be an element.
    Element parentElement = parentNode;
    renderTextBox.text = data;
    renderTextBox.style = parentElement.style;
  }
}

mixin NodeLifeCycle on Node {
  List<VoidCallback> _afterConnected = [];
  List<VoidCallback> _beforeDisconnected = [];

  void fireAfterConnected() {
    _afterConnected.forEach((VoidCallback fn) {
      fn();
    });
    _afterConnected = [];
  }

  void queueAfterConnected(VoidCallback callback) {
    _afterConnected.add(callback);
  }

  void fireBeforeDisconnected() {
    _beforeDisconnected.forEach((VoidCallback fn) {
      fn();
    });
    _beforeDisconnected = [];
  }

  void queueBeforeDisconnected(VoidCallback callback) {
    _beforeDisconnected.add(callback);
  }
}

abstract class Node extends EventTarget {
  int nodeId;
  List<Node> childNodes = [];
  Node parentNode;
  NodeType nodeType;
  String nodeName;

  Node(this.nodeType, this.nodeId, this.nodeName) {
    assert(nodeType != null);
    assert(nodeId != null);
    nodeName = nodeName ?? '';
  }

  // If node is on the tree, the root parent is body.
  bool get isConnected {
    Node parent = this;
    while (parent.parentNode != null) {
      parent = parent.parentNode;
    }
    return parent == ElementManager().getRootElement();
  }

  Node get firstChild => childNodes?.first;
  Node get lastChild => childNodes?.last;
  Node get nextSibling {
    if (parentNode == null) return null;
    int index = parentNode.childNodes?.indexOf(this);
    if (index == null) return null;
    return parentNode.childNodes[index + 1];
  }

  @mustCallSuper
  Node appendChild(Node child) {
    child.parentNode = this;
    this.childNodes.add(child);
    return child;
  }

  bool contains(Node child) {
    return childNodes.contains(child);
  }

  Node getRootNode() {
    Node root = this;
    while (root.parentNode != null) {
      root = root.parentNode;
    }
    return root;
  }

  @mustCallSuper
  Node insertBefore(Node newNode, Node referenceNode) {
    int referenceIndex = childNodes.indexOf(referenceNode);
    if (referenceIndex == -1) {
      return appendChild(newNode);
    } else {
      newNode.parentNode = this;
      childNodes.insert(referenceIndex, newNode);
      return newNode;
    }
  }

  @mustCallSuper
  Node removeChild(Node child) {
    if (childNodes.contains(child)) {
      childNodes.remove(child);
      child.parentNode = null;
    }
    return child;
  }

  @mustCallSuper
  Node replaceChild(Node newNode, Node oldNode) {
    Node replacedNode;
    if (childNodes.contains(oldNode)) {
      num referenceIndex = childNodes.indexOf(oldNode);
      oldNode.parentNode = null;
      replacedNode = oldNode;
      childNodes[referenceIndex] = newNode;
    } else {
      appendChild(newNode);
    }
    return replacedNode;
  }
}