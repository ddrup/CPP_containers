#include "s21_set.h"

template <class Key>
s21::set<Key>::set() : AVLTree<Key>() {}

template <class Key>
s21::set<Key>::set(std::initializer_list<Key> const& items) {
  for (auto item : items) insert(item);
}

template <class Key>
s21::set<Key>::set(const set<Key>& other) : AVLTree<Key>(other) {}

template <class Key>
s21::set<Key>::set(set<Key>&& other) noexcept : AVLTree<Key>(other) {}

template <class Key>
s21::set<Key>::~set() {}

template <class Key>
s21::set<Key>& s21::set<Key>::operator=(const set<Key>& other) {
  if (this != &other) {
    AVLTree<Key>::operator=(other);
  }
  return *this;
}

template <class Key>
s21::set<Key>& s21::set<Key>::operator=(set<Key>&& other) noexcept {
  if (this != &other) {
    AVLTree<Key>::operator=(other);
  }
  return *this;
}

template <class Key>
bool s21::set<Key>::contains(const Key& key) const {
  const typename s21::set<Key>::Iterator it = this->begin();
  for (; it != this->end(); it++) {
    if (key == (*it)) return true;
  }
  return false;
}

template <class Key>
std::pair<const typename s21::set<Key>::Iterator, bool> s21::set<Key>::insert(
    const Key& value) {
  bool flag = true;
  if (!this->contains(value)) {
    AVLTree<Key>::insert(value);
  } else
    flag = false;
  const typename s21::set<Key>::Iterator it = this->begin();
  for (; *it != value; it++)
    ;
  std::pair<decltype(it), bool> res(it, flag);
  return res;
}

template <class Key>
void s21::set<Key>::erase(typename s21::set<Key>::Iterator pos) {
  AVLTree<Key>::Remove(*pos);
}

template <class Key>
void s21::set<Key>::merge(const s21::set<Key>& other) {
  const typename s21::set<Key>::Iterator it = other.begin();
  for (; it != other.end(); it++) {
    insert(*it);
  }
}

template <class Key>
template <class... Args>
std::vector<std::pair<const typename s21::set<Key>::Iterator, bool>>
s21::set<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<const typename s21::set<Key>::Iterator, bool>> result;
  (result.push_back(this->insert(std::forward<Args>(args))), ...);
  return result;
}

template <class Key>
const typename s21::set<Key>::Iterator s21::set<Key>::find(
    const Key& key) const {
  const typename s21::set<Key>::Iterator it = this->begin();
  for (; it != this->end(); it++) {
    if (*it == key) break;
  }
  return it;
}