#ifndef S21_CONTAINERS_SRC_SET_S21_SET_H_
#define S21_CONTAINERS_SRC_SET_S21_SET_H_

#include "../AVLTree.h"

namespace s21 {

template <typename Key>
class set : public AVLTree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const Key&;
  using iterator = const typename set<Key>::Iterator;
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set<value_type>& other);
  set(set<value_type>&& other) noexcept;
  virtual ~set() override;
  set<value_type>& operator=(const set<value_type>& other);
  set<value_type>& operator=(set<value_type>&& other) noexcept;

  std::pair<iterator, bool> insert(const value_type& value);

  bool contains(const key_type& key) const;
  void erase(iterator pos);
  void merge(const set<value_type>& other);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  iterator find(const key_type& key) const;
};
}  // namespace s21

#include "s21_set.cc"

#endif  // S21_CONTAINERS_SRC_SET_S21_SET_H_