#ifndef S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
#define S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_

#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {

template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  array operator=(array &&a) noexcept;
  array operator=(const array &a);
  ~array() = default;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  reference front();
  reference back();
  iterator data() noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array &other) noexcept;
  void fill(const_reference value);

 private:
  value_type array_elements_[N] = {};
  size_type size_;
};

}  // namespace s21

#include "s21_array.tpp"

#endif  // S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_