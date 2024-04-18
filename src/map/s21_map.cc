#include "s21_map.h"

template <class Key, class T>
s21::map<Key, T>::map() : AVLTree<s21::pair<const Key, T>>() {}

template <class Key, class T>
s21::map<Key, T>::map(
    std::initializer_list<std::pair<const Key, T>> const& items) {
  for (auto item : items) insert(item);
}

template <class Key, class T>
s21::map<Key, T>::map(const map<Key, T>& other)
    : AVLTree<s21::pair<const Key, T>>(other) {}

template <class Key, class T>
s21::map<Key, T>::map(map<Key, T>&& other) noexcept
    : AVLTree<s21::pair<const Key, T>>(other) {}

template <class Key, class T>
s21::map<Key, T>::~map() {}

template <class Key, class T>
s21::map<Key, T>& s21::map<Key, T>::operator=(const map<Key, T>& other) {
  if (this != &other) {
    AVLTree<s21::pair<const Key, T>>::operator=(other);
  }
  return *this;
}

template <class Key, class T>
s21::map<Key, T>& s21::map<Key, T>::operator=(map<Key, T>&& other) noexcept {
  if (this != &other) {
    AVLTree<s21::pair<const Key, T>>::operator=(other);
  }
  return *this;
}

template <class Key, class T>
std::pair<typename s21::map<Key, T>::Iterator, bool> s21::map<Key, T>::insert(
    const std::pair<const Key, T>& value) {
  s21::pair<const Key, T> val(value.first, value.second);
  bool flag = true;
  if (!this->contains(val.first))
    AVLTree<s21::pair<const Key, T>>::insert(val);
  else
    flag = false;
  typename s21::map<Key, T>::Iterator it = this->begin();
  for (; (*it).first != val.first; ++it)
    ;
  std::pair<decltype(it), bool> res(it, flag);
  return res;
}

template <class Key, class T>
std::pair<typename s21::map<Key, T>::Iterator, bool> s21::map<Key, T>::insert(
    const Key& key, const T& obj) {
  return insert(std::pair<const Key, T>(key, obj));
}

template <class Key, class T>
std::pair<typename s21::map<Key, T>::Iterator, bool>
s21::map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  AVLTree<s21::pair<const Key, T>>::insert(s21::pair<const Key, T>(key, obj));
  typename s21::map<Key, T>::Iterator it = this->begin();
  for (; (*it).first != key; ++it)
    ;
  bool result = true;
  return std::pair<typename s21::map<Key, T>::Iterator, bool>(it, result);
}

template <class Key, class T>
bool s21::map<Key, T>::contains(const Key& key) const {
  typename s21::map<Key, T>::Iterator it = this->begin();
  for (; it != this->end(); ++it) {
    if (key == (*it).first) return true;
  }
  return false;
}

template <class Key, class T>
void s21::map<Key, T>::erase(typename s21::map<Key, T>::Iterator pos) {
  AVLTree<s21::pair<const Key, T>>::Remove(*pos);
}

template <class Key, class T>
T& s21::map<Key, T>::at(const Key& key) {
  auto it = this->begin();
  for (; it != this->end(); ++it) {
    if ((*it).first == key) break;
  }
  if (it == this->end()) throw std::out_of_range("this key was not found");
  return (*it).second;
}

template <class Key, class T>
const T& s21::map<Key, T>::at(const Key& key) const {
  auto it = this->begin();
  for (; it != this->end(); ++it) {
    if ((*it).first == key) break;
  }
  if (it == this->end()) throw std::out_of_range("this key was not found");
  return (*it).second;
}

template <class Key, class T>
T& s21::map<Key, T>::operator[](const Key& key) {
  auto it = this->begin();
  for (; it != this->end(); ++it) {
    if ((*it).first == key) break;
  }
  if (it == this->end()) {
    insert(key, T());
    return this->at(key);
  }
  return (*it).second;
}

template <class Key, class T>
void s21::map<Key, T>::merge(const s21::map<Key, T>& other) {
  const typename s21::map<Key, T>::Iterator it = other.begin();
  for (; it != other.end(); it++) {
    insert(*it);
  }
}

template <class Key, class T>
template <class... Args>
std::vector<std::pair<typename s21::map<Key, T>::Iterator, bool>>
s21::map<Key, T>::insert_many(Args&&... args) {
  std::vector<std::pair<typename s21::map<Key, T>::Iterator, bool>> result;
  (result.push_back(this->insert(std::forward<Args>(args))), ...);
  return result;
}
