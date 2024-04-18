#ifndef CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_

#include <iostream>

#include "../list/s21_list.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(stack const &s);
  stack &operator=(stack &&s) noexcept;

  const_reference top();
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <class... Args>
  void insert_many_front(Args &&...args);

 private:
  Container list_;
};
}  // namespace s21

#include "s21_stack.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_STACK_S21_STACK_H_