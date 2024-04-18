#ifndef S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_
#define S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_

#include <cstdlib>
#include <iostream>
#include <limits>

namespace s21 {

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using pointer = T *;

  template <class value_type>
  class VectorIterator {
   public:
    VectorIterator() = default;
    VectorIterator(value_type *ptr) : p_(ptr) {}
    reference operator*() { return *p_; }
    VectorIterator &operator++() {
      p_++;
      return *this;
    }
    VectorIterator operator++(int) {
      VectorIterator extra(p_);
      p_++;
      return extra;
    }
    VectorIterator &operator--() {
      p_--;
      return *this;
    }
    VectorIterator operator--(int) {
      VectorIterator extra(p_);
      p_--;
      return extra;
    }
    bool operator==(const VectorIterator &it) const { return p_ == it.p_; }
    bool operator!=(const VectorIterator &it) const { return p_ != it.p_; }
    VectorIterator operator+(int n) {
      for (int i = 0; i < n; i++) ++p_;
      return *this;
    }
    VectorIterator operator-(int n) {
      for (int i = 0; i < n; i++) --p_;
      return *this;
    }
    value_type *SetPtr() { return p_; }
    friend int operator-(VectorIterator a, VectorIterator b) {
      int i = 0;
      while (a != b) {
        i++;
        a++;
      }
      return i;
    }

   private:
    value_type *p_;
  };

  template <class value_type>
  class VectorConstIterator {
   public:
    VectorConstIterator() = default;
    VectorConstIterator(value_type *ptr) : p_(ptr) {}
    const_reference operator*() { return *p_; }
    const VectorConstIterator &operator++() {
      p_++;
      return *this;
    }
    VectorConstIterator operator++(int) {
      VectorConstIterator extra(p_);
      p_++;
      return extra;
    }
    const VectorConstIterator &operator--() {
      p_--;
      return *this;
    }
    VectorConstIterator operator--(int) {
      VectorConstIterator extra(p_);
      p_--;
      return extra;
    }
    bool operator==(const VectorConstIterator &it) const { return p_ == it.p_; }
    bool operator!=(const VectorConstIterator &it) const { return p_ != it.p_; }
    VectorConstIterator operator+(int n) {
      for (int i = 0; i < n; i++) ++p_;
      return *this;
    }
    VectorConstIterator operator-(int n) {
      for (int i = 0; i < n; i++) --p_;
      return *this;
    }

   private:
    value_type *p_;
  };

  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector operator=(vector &&v) noexcept;
  vector operator=(const vector &v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T *data();

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <class... Args>
  iterator insert_many(iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // S21_CONTAINERS_SRC_VECTOR_S21_VECTOR_H_