#ifndef CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_

#include <iostream>

#include "../list/s21_list.h"

namespace s21 {

template <class T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &s);
  queue(queue &&s);
  ~queue();
  queue &operator=(queue const &s);
  queue &operator=(queue &&s) noexcept;

  const_reference front();
  const_reference back();
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  Container list_;
};
}  // namespace s21

#include "s21_queue.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_QUEUE_S21_QUEUE_H_