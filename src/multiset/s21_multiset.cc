#include "s21_multiset.h"

template <class Key>
s21::multiset<Key>::multiset() : AVLTree<Key>() {}

template <class Key>
s21::multiset<Key>::multiset(std::initializer_list<Key> const& items) {
  for (auto item : items) insert(item);
}

template <class Key>
s21::multiset<Key>::multiset(const multiset<Key>& other)
    : AVLTree<Key>(other) {}

template <class Key>
s21::multiset<Key>::multiset(multiset<Key>&& other) noexcept
    : AVLTree<Key>(other) {}

template <class Key>
s21::multiset<Key>::~multiset() {}

template <class Key>
s21::multiset<Key>& s21::multiset<Key>::operator=(const multiset<Key>& other) {
  if (this != &other) {
    AVLTree<Key>::operator=(other);
  }
  return *this;
}

template <class Key>
s21::multiset<Key>& s21::multiset<Key>::operator=(
    multiset<Key>&& other) noexcept {
  if (this != &other) {
    AVLTree<Key>::operator=(other);
  }
  return *this;
}

template <class Key>
bool s21::multiset<Key>::contains(const Key& key) const {
  const typename s21::multiset<Key>::Iterator it = this->begin();
  for (; it != this->end(); it++) {
    if (key == (*it)) return true;
  }
  return false;
}

template <class Key>
const typename s21::multiset<Key>::Iterator s21::multiset<Key>::insert(
    const Key& value) {
  AVLTree<Key>::insert_multi(value);
  const typename s21::multiset<Key>::Iterator it = this->begin();
  for (; *it != value; it++)
    ;
  return it;
}

template <class Key>
void s21::multiset<Key>::erase(typename s21::multiset<Key>::Iterator pos) {
  AVLTree<Key>::Remove(*pos);
}

template <class Key>
void s21::multiset<Key>::merge(const s21::multiset<Key>& other) {
  const typename s21::multiset<Key>::Iterator it = other.begin();
  for (; it != other.end(); it++) {
    insert(*it);
  }
}

template <class Key>
template <class... Args>
std::vector<std::pair<const typename s21::multiset<Key>::Iterator, bool>>
s21::multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<const typename s21::multiset<Key>::Iterator, bool>>
      result;
  (result.push_back(
       std::pair<const typename s21::multiset<Key>::Iterator, bool>(
           this->insert(std::forward<Args>(args)), true)),
   ...);
  return result;
}

template <class Key>
const typename s21::multiset<Key>::Iterator s21::multiset<Key>::find(
    const Key& key) const {
  const typename s21::multiset<Key>::Iterator it = this->begin();
  for (; it != this->end(); it++) {
    if (*it == key) break;
  }
  return it;
}

template <class Key>
size_t s21::multiset<Key>::count(const Key& key) {
  const typename s21::multiset<Key>::Iterator it = this->begin();
  size_t counter = 0;
  for (; it != this->end(); it++) {
    if (*it == key) break;
  }
  for (; it != this->end() && *it == key; it++, ++counter)
    ;
  return counter;
}

template <class Key>
const typename s21::multiset<Key>::Iterator s21::multiset<Key>::lower_bound(
    const Key& key) {
  return find(key);
}

template <class Key>
const typename s21::multiset<Key>::Iterator s21::multiset<Key>::upper_bound(
    const Key& key) {
  const typename s21::multiset<Key>::Iterator it = find(key);
  for (; it != this->end() && *it == key; it++)
    ;
  return it;
}

template <class Key>
std::pair<const typename s21::multiset<Key>::Iterator,
          const typename s21::multiset<Key>::Iterator>
s21::multiset<Key>::equal_range(const Key& key) {
  return std::pair<const typename s21::multiset<Key>::Iterator,
                   const typename s21::multiset<Key>::Iterator>(
      find(key), upper_bound(key));
}