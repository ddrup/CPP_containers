#include "AVLTree.h"

template <class T>
AVLTreeNode<T>::AVLTreeNode()
    : balanceFactor_(0),
      height_(1),
      val_(T()),
      right_(nullptr),
      left_(nullptr) {}

template <class T>
AVLTreeNode<T>::AVLTreeNode(const T& x)
    : balanceFactor_(0), height_(1), val_(x), right_(nullptr), left_(nullptr) {}

template <class T>
AVLTreeNode<T>::~AVLTreeNode() {
  if (left_) delete left_;
  left_ = nullptr;
  if (right_) delete right_;
  right_ = nullptr;
}

template <class T>
size_t AVLTree<T>::Height(AVLTreeNode<T>* node) const {
  return node ? node->height_ : 0;
}

template <class T>
int AVLTree<T>::BFactor(AVLTreeNode<T>* node) const {
  return Height(node->right_) - Height(node->left_);
}

template <class T>
void AVLTree<T>::FixHeight(AVLTreeNode<T>* node) const {
  size_t hLeft = Height(node->left_);
  size_t hRight = Height(node->right_);
  node->height_ = (hLeft > hRight ? hLeft : hRight) + 1;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::SingleRotateRight(AVLTreeNode<T>* nodeA) {
  AVLTreeNode<T>* nodeB = nodeA->left_;
  nodeA->left_ = nodeB->right_;
  nodeB->right_ = nodeA;
  FixHeight(nodeA);
  FixHeight(nodeB);
  return nodeB;  //вернм новый корень
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::SingleRotateLeft(AVLTreeNode<T>* nodeA) {
  AVLTreeNode<T>* nodeB = nodeA->right_;
  nodeA->right_ = nodeB->left_;
  nodeB->left_ = nodeA;
  FixHeight(nodeA);
  FixHeight(nodeB);
  return nodeB;  //вернм новый корень
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::Balance(AVLTreeNode<T>* node) {
  FixHeight(node);
  if (BFactor(node) == 2) {
    if (BFactor(node->right_) < 0)
      node->right_ = SingleRotateRight(node->right_);  //двойной поворот
    return SingleRotateLeft(node);
  }
  if (BFactor(node) == -2) {
    if (BFactor(node->left_) > 0) node->left_ = SingleRotateLeft(node->left_);
    return SingleRotateRight(node);
  }
  return node;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::AVLInsert(AVLTreeNode<T>* node, const T& data) {
  if (node == nullptr) return new AVLTreeNode<T>(data);
  if (data < node->val_) {
    node->left_ = AVLInsert(node->left_, data);
  } else if (node->val_ < data) {
    node->right_ = AVLInsert(node->right_, data);
  } else
    node->val_ = data;
  return Balance(node);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::AVLInsertMulti(AVLTreeNode<T>* node,
                                           const T& data) {
  if (node == nullptr) return new AVLTreeNode<T>(data);
  if (data < node->val_) {
    node->left_ = AVLInsertMulti(node->left_, data);
  } else {
    node->right_ = AVLInsertMulti(node->right_, data);
  }
  return Balance(node);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::FindMin(AVLTreeNode<T>* node) {
  return node->left_ ? FindMin(node->left_) : node;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::RemoveMin(AVLTreeNode<T>* node) {
  if (node->left_ == nullptr) return node->right_;
  node->left_ = RemoveMin(node->left_);
  return Balance(node);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::AVLRemove(AVLTreeNode<T>* node, const T& data) {
  if (node == nullptr) return 0;
  if (data < node->val_) {
    node->left_ = AVLRemove(node->left_, data);
  } else if (node->val_ < data) {
    node->right_ = AVLRemove(node->right_, data);
  } else {  // k == node->val_
    AVLTreeNode<T>* left = node->left_;
    AVLTreeNode<T>* rigth = node->right_;
    node->left_ = nullptr;
    node->right_ = nullptr;
    delete node;
    if (rigth == nullptr) return left;
    AVLTreeNode<T>* min = FindMin(rigth);
    min->right_ = RemoveMin(rigth);
    min->left_ = left;
    return Balance(min);
  }
  return Balance(node);
}

template <class T>
AVLTree<T>::~AVLTree() {
  delete root_;
  root_ = nullptr;
}

template <class T>
AVLTree<T>::AVLTree() : root_(nullptr) {}

template <class T>
void AVLTree<T>::insert(const T& data) {
  root_ = AVLInsert(root_, data);
}

template <class T>
void AVLTree<T>::insert_multi(const T& data) {
  root_ = AVLInsertMulti(root_, data);
}

template <class T>
void AVLTree<T>::Remove(const T& data) {
  root_ = AVLRemove(root_, data);
}

template <class T>
AVLTree<T>::AVLTree(std::initializer_list<T> const& items) : AVLTree<T>() {
  for (T item : items) {
    root_ = AVLInsert(root_, item);
  }
}

template <class T>
AVLTree<T>::AVLTree(AVLTree<T>&& other) noexcept {
  std::swap(root_, other.root_);
  other.root_ = nullptr;
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& other) : AVLTree<T>() {
  const AVLTree<T>::Iterator it = other.begin();
  for (; it != other.end(); it++) {
    root_ = AVLInsert(root_, *it);
  }
}

template <class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& other) {
  if (this != &other) {
    AVLTree<T> tmp(other);
    std::swap(this->root_, tmp.root_);
  }
  return *this;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree<T>&& other) noexcept {
  if (this != &other) {
    AVLTree<T> tmp(other);
    std::swap(this->root_, tmp.root_);
    other.root_ = nullptr;
  }
  return *this;
}

template <class T>
size_t AVLTree<T>::size() const {
  if (root_ == nullptr) return 0;
  return NodeCount(root_);
}

template <class T>
size_t AVLTree<T>::NodeCount(AVLTreeNode<T> const* node) const {
  if (node->left_ == nullptr && node->right_ == nullptr) return 1;
  size_t countLeftNode = 0;
  size_t countRightNode = 0;
  if (node->left_ != nullptr) countLeftNode = NodeCount(node->left_);
  if (node->right_ != nullptr) countRightNode = NodeCount(node->right_);
  return countLeftNode + countRightNode + 1;
}

template <class T>
bool AVLTree<T>::empty() const {
  return root_ ? false : true;
}

template <class T>
size_t AVLTree<T>::max_size() const {
  return SIZE_MAX / sizeof(AVLTreeNode<T>) / 2;
}

template <class T>  // TODO нужно убрать в конце
std::vector<std::vector<T>> AVLTree<T>::LevelOrder() {
  std::vector<std::vector<T>> result;
  std::vector<T> levelTree;
  if (!root_) {
    return result;
  }
  std::queue<AVLTreeNode<T>*> queue;
  queue.push(root_);
  queue.push(nullptr);  // маркер
  while (!queue.empty()) {
    AVLTreeNode<T>* current = queue.front();
    queue.pop();

    if (current) {
      levelTree.push_back(current->val_);
      if (current->left_) queue.push(current->left_);
      if (current->right_) queue.push(current->right_);
    } else {
      result.push_back(levelTree);
      levelTree.clear();
      if (!queue.empty()) queue.push(nullptr);
    }
  }
  return result;
}

template <class T>
typename AVLTree<T>::Iterator AVLTree<T>::begin() {
  return AVLTree<T>::Iterator(root_);
}

template <class T>
typename AVLTree<T>::Iterator AVLTree<T>::end() {
  AVLTree<T>::Iterator it(root_);
  for (; !it.EndOfList(); ++it) {
  }
  return it;
}

template <class T>
const typename AVLTree<T>::Iterator AVLTree<T>::begin() const {
  return AVLTree<T>::Iterator(root_);
}

template <class T>
const typename AVLTree<T>::Iterator AVLTree<T>::end() const {
  AVLTree<T>::Iterator it(root_);
  for (; !it.EndOfList(); ++it) {
  }
  return it;
}

template <class T>
void AVLTree<T>::clear() {
  delete root_;
  root_ = nullptr;
}

template <class T>
void AVLTree<T>::swap(AVLTree<T>& other) {
  std::swap(root_, other.root_);
}