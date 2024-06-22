#ifndef __S21_CONTAINERS_EXTRA__
#define __S21_CONTAINERS_EXTRA__

#include <math.h>
#include <stdlib.h>

#include <iomanip>
#include <iostream>

namespace s21 {
template <typename T>
class Node {
 public:
  Node() {}

  Node(Node* next, Node* prev, T* value) {
    this->next = next;
    this->prev = prev;
    this->value = value;
  }

  Node* next;
  Node* prev;
  T* value;
};

template <typename T1, typename T2>
class BinaryNode {
 public:
  BinaryNode() {
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->value = new std::pair<T1, T2>();
  }

  BinaryNode(BinaryNode* parent, T1 key, T2 value) {
    this->parent = parent;
    this->left = nullptr;
    this->right = nullptr;
    this->value = new std::pair<T1, T2>(key, value);
  }

  BinaryNode* parent;
  BinaryNode* left;
  BinaryNode* right;

  std::pair<T1, T2>* value;
};

template <typename T>
class BinaryNodeT {
 public:
  BinaryNodeT() {
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->value = new T();
  }

  BinaryNodeT(BinaryNodeT* parent, T key) {
    this->parent = parent;
    this->left = nullptr;
    this->right = nullptr;
    this->value = new T(key);
  }

  BinaryNodeT* parent;
  BinaryNodeT* left;
  BinaryNodeT* right;

  T* value;
};

template <typename T>
class Iterator {
 public:
  Iterator() {}
  Iterator(Node<T>* node) { this->node = node; }

  bool operator!=(Iterator<T> other) { return (this->node != other.node); }

  bool operator==(Iterator<T> other) { return (this->node == other.node); }

  T& operator*() { return *(this->node->value); }

  Node<T>* node;
};

template <typename T1, typename T2>
class BinaryIterator {
 public:
  BinaryIterator() {}
  BinaryIterator(BinaryNode<T1, T2>* node) { this->node = node; }

  bool operator!=(BinaryIterator<T1, T2> other) {
    return (this->node != other.node);
  }

  bool operator==(BinaryIterator<T1, T2> other) {
    return (this->node == other.node);
  }

  std::pair<const T1, T2>& operator*() {
    return (std::pair<const T1, T2>&)*this->node->value;
  }

  BinaryNode<T1, T2>* node;
};

template <typename T>
class BinaryIteratorT {
 public:
  BinaryIteratorT() {}
  BinaryIteratorT(BinaryNodeT<T>* node) { this->node = node; }

  bool operator!=(BinaryIteratorT<T> other) {
    return (this->node->value != other.node->value);
  }

  bool operator==(BinaryIteratorT<T> other) {
    return (this->node == other.node);
  }

  T& operator*() { return (T&)*this->node->value; }

  BinaryNodeT<T>* node;
};
}  // namespace s21

#endif