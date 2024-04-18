#ifndef S21_CONTAINERS_SRC_LIST_S21_LIST_H_
#define S21_CONTAINERS_SRC_LIST_S21_LIST_H_

#include <cstdlib>
#include <iostream>
#include <limits>

namespace s21 {

template <class T>
struct Node {
 public:
  using value_type = T;

  value_type data;
  Node *next;
  Node *prev;
  Node(value_type data) : data(data), next(nullptr), prev(nullptr) {}
};

template <class T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  template <class value_type>
  class ListIterator {
   public:
    ListIterator() : it_(nullptr) {}
    ListIterator(Node<value_type> *it) : it_(it) {}

    reference operator*() const {
      if (it_ == nullptr) {
        throw std::invalid_argument("it_ == nullptr");
      }
      return it_->data;
    }
    reference operator->() const {
      if (it_ == nullptr) {
        throw std::invalid_argument("it_ == nullptr");
      }
      return it_->data;
    }
    ListIterator operator++(int) {
      it_ = it_->next;
      return *this;
    }
    ListIterator operator--(int) {
      if (it_ == list_->tail_->next)
        it_ = list_->tail_;
      else
        it_ = it_->prev;
      return *this;
    }

    ListIterator &operator++() {
      it_ = it_->next;
      return *this;
    }
    ListIterator &operator--() {
      if (it_ == list_->tail_->next)
        it_ = list_->tail_;
      else
        it_ = it_->prev;
      return *this;
    }

    ListIterator operator+(size_type value) {
      for (size_type i = 0; i < value; i++) it_ = it_->next;
      return *this;
    }
    ListIterator operator-(size_type value) {
      for (size_type i = 0; i < value; i++) it_ = it_->prev;
      return *this;
    }

    bool operator==(const ListIterator &other) const noexcept {
      return other.it_ == it_;
    }
    bool operator!=(const ListIterator &other) const noexcept {
      return other.it_ != it_;
    }
    bool operator>(const ListIterator &other) const noexcept {
      return it_ > other.it_;
    }
    bool operator<(const ListIterator &other) const noexcept {
      return it_ < other.it_;
    }
    Node<value_type> *GetIt() { return it_; }

   protected:
    ListIterator(Node<value_type> *it, const list<value_type> *list)
        : it_(it), list_(list) {}
    Node<value_type> *it_;
    const list<value_type> *list_;
    friend class list<value_type>;
  };

  template <class value_type>
  class ListConstIterator : public ListIterator<value_type> {
   public:
    ListConstIterator() : ListIterator<value_type>::ListIterator(nullptr) {}
    ListConstIterator(Node<value_type> *it)
        : ListIterator<value_type>::ListIterator(it) {}
    ListConstIterator(Node<value_type> *it, const list<value_type> *list)
        : ListIterator<value_type>::ListIterator(it, list) {}
    const_reference operator*() {
      if (ListIterator<value_type>::GetIt() == nullptr) {
        throw std::invalid_argument("it_ == nullptr");
      }
      return ListIterator<value_type>::GetIt()->data;
    }
    const_reference operator->() {
      if (ListIterator<value_type>::GetIt() == nullptr) {
        throw std::invalid_argument("it_ == nullptr");
      }
      return ListIterator<value_type>::GetIt()->data;
    }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  list operator=(list &&l) noexcept;
  list operator=(const list &l);
  ~list();

  const_reference front() const;
  const_reference back() const;

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

  // extra functions
  void quick_sort(iterator start, iterator end);
  typename list<value_type>::iterator partition(iterator start, iterator end);

 private:
  Node<value_type> *head_;
  Node<value_type> *tail_;
  size_type size_;
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_CONTAINERS_SRC_LIST_S21_LIST_H_