#include "AVLTree.h"

template <class T>
AVLTreeNode<T>* AVLTree<T>::Iterator::GoFarLeft(AVLTreeNode<T>* node) const {
  if (node == nullptr) return nullptr;
  while (node->left_) {
    stackNode.push(node);
    node = node->left_;
  }
  return node;
}

template <class T>
AVLTree<T>::Iterator::Iterator()
    : root_(nullptr), current_(nullptr), iterationComplete(true) {}

template <class T>
AVLTree<T>::Iterator::Iterator(AVLTreeNode<T>* root) : root_(root) {
  iterationComplete = (root_ == nullptr);
  current_ = GoFarLeft(root_);
}

template <class T>
void AVLTree<T>::Iterator::Reset() const {
  iterationComplete = (root_ == nullptr);
  stackNode = std::stack<AVLTreeNode<T>*>();
  current_ = GoFarLeft(root_);
}

template <class T>
void AVLTree<T>::Iterator::Next() const {
  if (iterationComplete) {
    throw std::logic_error("all nodes are passed");
  }
  if (current_->right_) {
    stackNodeRevers.push(current_);
    current_ = GoFarLeft(current_->right_);
  } else if (!stackNode.empty()) {
    stackNodeRevers.push(current_);
    current_ = stackNode.top();
    stackNode.pop();
  } else {
    iterationComplete = true;
    stackNodeRevers.push(current_);
    current_ = nullptr;
  }
}

template <class T>
void AVLTree<T>::Iterator::Last() const {
  if (stackNodeRevers.empty()) {
    throw std::logic_error("all nodes are passed");
  }
  current_ = stackNodeRevers.top();
  stackNodeRevers.pop();
}

template <class T>
T AVLTree<T>::Iterator::Data() const {
  return current_->val_;
}

template <class T>
bool AVLTree<T>::Iterator::EndOfList() const {
  return iterationComplete;
}

template <class T>
bool AVLTree<T>::Iterator::BeginOfList() const {
  return stackNodeRevers.empty();
}

template <class T>
AVLTree<T>::Iterator::Iterator(const AVLTree<T>::Iterator& other) {
  current_ = other.current_;
  root_ = other.root_;
  stackNode = other.stackNode;
  stackNodeRevers = other.stackNodeRevers;
}

template <class T>
AVLTree<T>::Iterator::Iterator(AVLTree<T>::Iterator&& other) noexcept {
  this->swap(other);
  other.stackNode = std::stack<AVLTreeNode<T>*>();
  other.stackNodeRevers = std::stack<AVLTreeNode<T>*>();
  other.root_ = nullptr;
  other.current_ = nullptr;
}

template <class T>
void AVLTree<T>::Iterator::swap(AVLTree<T>::Iterator& other) {
  std::swap(current_, other.current_);
  std::swap(root_, other.root_);
  std::swap(stackNode, other.stackNode);
  std::swap(stackNodeRevers, other.stackNodeRevers);
}

template <class T>
T& AVLTree<T>::Iterator::operator++() {
  this->Next();
  return current_->val_;
}

template <class T>
T AVLTree<T>::Iterator::operator++(int) const {
  T tmpVal(current_->val_);
  this->Next();
  return tmpVal;
}

template <class T>
T& AVLTree<T>::Iterator::operator*() {
  return current_->val_;
}

template <class T>
const T& AVLTree<T>::Iterator::operator*() const {
  return current_->val_;
}

template <class T>
bool AVLTree<T>::Iterator::operator==(const Iterator& it) const {
  return (stackNode == it.stackNode && stackNodeRevers == it.stackNodeRevers &&
          current_ == it.current_ && root_ == it.root_);
}

template <class T>
bool AVLTree<T>::Iterator::operator!=(const Iterator& it) const {
  return (stackNode != it.stackNode || stackNodeRevers != it.stackNodeRevers ||
          current_ != it.current_ || root_ != it.root_);
}

template <class T>
typename AVLTree<T>::Iterator& AVLTree<T>::Iterator::operator=(
    const AVLTree<T>::Iterator& other) {
  if (this != &other) AVLTree<T>::Iterator(other).swap(*this);
  return *this;
}

template <class T>
typename AVLTree<T>::Iterator& AVLTree<T>::Iterator::operator=(
    AVLTree<T>::Iterator&& other) noexcept {
  if (this != &other) {
    AVLTree<T>::Iterator(other).swap(*this);
    other.stackNode = std::stack<AVLTreeNode<T>*>();
    other.stackNode = std::stack<AVLTreeNode<T>*>();
    other.root_ = nullptr;
    other.current_ = nullptr;
  }
  return *this;
}

template <class T>
T& AVLTree<T>::Iterator::operator--() {
  this->Last();
  return current_->val_;
}

template <class T>
T AVLTree<T>::Iterator::operator--(int) const {
  if (current_ == nullptr) {
    this->Last();
    return current_->val_;
  }
  T tmpVal(current_->val_);
  this->Last();
  return tmpVal;
}