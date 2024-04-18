#ifndef S21_CONTAINERS_SRC_MAP_S21_MAP_H_
#define S21_CONTAINERS_SRC_MAP_S21_MAP_H_

#include "../AVLTree.h"

namespace s21 {

template <class Key, class T>
class pair : public std::pair<const Key, T> {
 public:
  pair() : std::pair<const Key, T>() {}
  pair(const Key& first, const T& second)
      : std::pair<const Key, T>(first, second) {}
  pair(const pair& other) : std::pair<const Key, T>(other) {}
  pair(pair&& other) noexcept : std::pair<const Key, T>(std::move(other)){};

  s21::pair<const Key, T>& operator=(const s21::pair<const Key, T>& other) {
    if (this != &other) {
      this->second = other.second;
    }
    return *this;
  }
};

template <class Key, class T>
bool operator<(const pair<const Key, T>& lhs, const pair<const Key, T>& rhs) {
  return lhs.first < rhs.first;
}

template <class Key, class T>
class map : public AVLTree<pair<const Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename map<Key, T>::Iterator;
  using const_iterator = const typename map<Key, T>::Iterator;
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map<key_type, mapped_type>& other);
  map(map<key_type, mapped_type>&& other) noexcept;
  virtual ~map() override;
  map<key_type, mapped_type>& operator=(
      const map<key_type, mapped_type>& other);
  map<key_type, mapped_type>& operator=(
      map<key_type, mapped_type>&& other) noexcept;

  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  bool contains(const key_type& key) const;
  void erase(iterator pos);
  void merge(const map<key_type, mapped_type>& other);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  mapped_type& at(const key_type& key);
  const mapped_type& at(const key_type& key) const;
  mapped_type& operator[](const key_type& key);
};
}  // namespace s21

#include "s21_map.cc"

#endif  // S21_CONTAINERS_SRC_MAP_S21_MAP_H_