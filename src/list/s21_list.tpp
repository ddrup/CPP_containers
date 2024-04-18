namespace s21 {

template <class value_type>
list<value_type>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <class value_type>
list<value_type>::list(size_type n) : list() {
  for (size_type i = 0; i < n; i++) {
    push_back(0);
  }
}

template <class value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : list() {
  for (value_type i : items) {
    push_back(i);
  }
}

template <class value_type>
list<value_type>::list(const list &l) : list() {
  Node<value_type> *node = l.head_;
  for (size_type i = 0; i < l.size(); i++) {
    push_back(node->data);
    node = node->next;
  }
}

template <class value_type>
list<value_type>::list(list &&l) noexcept {
  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;
  l.size_ = 0;
  l.head_ = nullptr;
  l.tail_ = nullptr;
}

template <class value_type>
list<value_type> list<value_type>::operator=(const list &l) {
  if (this == &l) {
    return *this;
  }
  this->~list();
  for (iterator it = l.begin(); it != l.end(); it++) {
    push_back(it.GetIt()->data);
  }
  return *this;
}

template <class value_type>
list<value_type> list<value_type>::operator=(list &&l) noexcept {
  if (this == &l) {
    return *this;
  }
  this->~list();
  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;
  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;
  return *this;
}

template <class value_type>
list<value_type>::~list() {
  clear();
}

// public methods for access the elements

template <class value_type>
typename list<value_type>::iterator list<value_type>::begin() const {
  return iterator(head_, this);
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::end() const {
  return iterator(tail_->next, this);
}

template <class value_type>
typename list<value_type>::const_iterator list<value_type>::cbegin() const {
  return const_iterator(head_, this);
}

template <class value_type>
typename list<value_type>::const_iterator list<value_type>::cend() const {
  return const_iterator(tail_->next, this);
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("List is empty!");
  }
  return head_->data;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("List is empty!");
  }
  return tail_->data;
}

// public methods for get information about the container

template <class value_type>
bool list<value_type>::empty() const {
  return size_ == 0;
}

template <class value_type>
typename list<value_type>::size_type list<value_type>::size() const {
  return size_;
}

template <class value_type>
typename list<value_type>::size_type list<value_type>::max_size() const {
  return (std::numeric_limits<size_type>::max() / sizeof(Node<value_type>) / 2);
}

// public methods for changint the container

template <class value_type>
void list<value_type>::push_back(const_reference value) {
  Node<value_type> *node = new Node<value_type>(value);
  if (size_ == 0) {
    head_ = node;
    tail_ = node;
  } else {
    tail_->next = node;
    node->prev = tail_;
    tail_ = node;
  }
  size_++;
}

template <class value_type>
void list<value_type>::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("list don`t have elements!");
  }

  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    tail_ = tail_->prev;
    delete tail_->next;
    tail_->next = nullptr;
  }

  size_--;
}

template <class value_type>
void list<value_type>::push_front(const_reference value) {
  Node<value_type> *node = new Node<value_type>(value);
  if (size_ == 0) {
    head_ = node;
    tail_ = node;
  } else {
    node->next = head_;
    head_->prev = node;
    head_ = node;
  }
  size_++;
}

template <class value_type>
void list<value_type>::pop_front() {
  if (empty() == true) {
    throw std::out_of_range("List is empty");
  }

  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    head_ = head_->next;
    delete head_->prev;
    head_->prev = nullptr;
  }
  size_--;
}

template <class value_type>
void list<value_type>::clear() {
  while (empty() == false) {
    pop_back();
  }
}

template <class value_type>
void list<value_type>::swap(list &other) {
  if (this != &other) {
    list<value_type> list(other);
    other.clear();
    while (size_ != 0) {
      other.push_back(head_->data);
      pop_front();
    }
    while (list.size() != 0) {
      push_back(list.head_->data);
      list.pop_front();
    }
  }
}

template <class value_type>
void list<value_type>::merge(list &other) {
  if (&other != this) {
    iterator it = begin();
    if (it == nullptr) {
      while (!other.empty()) {
        push_back(other.head_->data);
        other.pop_front();
      }
    }
    while (other.empty() == false) {
      if (other.head_->data < *it) {
        if (it == begin())
          push_front(other.head_->data);
        else if (it == end())
          push_back(other.head_->data);
        else {
          insert(it, other.head_->data);
        }
        other.pop_front();
      } else {
        it++;
        if (it == end()) {
          while (!other.empty()) {
            push_back(other.head_->data);
            other.pop_front();
          }
        }
      }
    }
  }
}

template <class value_type>
void list<value_type>::reverse() {
  Node<value_type> *node = tail_;
  tail_ = head_;
  head_ = node;
  for (int i = 0; i < (int)size(); i++) {
    Node<value_type> *node1 = node->next;
    node->next = node->prev;
    node->prev = node1;
    node = node->next;
  }
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  iterator it = begin();
  while (it != pos) {
    it++;
  }
  if (it == head_) {
    push_front(value);
    --it;
  } else if (it == tail_->next)
    push_back(value);
  else {
    Node<value_type> *node = new Node<value_type>(value);
    Node<value_type> *node_prev = it.it_->prev;
    node_prev->next = node;
    node->prev = node_prev;
    node->next = it.it_;
    it.it_->prev = node;
    --it;
    size_++;
  }
  return it;
}

template <class value_type>
void list<value_type>::erase(iterator pos) {
  iterator it = begin();
  while (it != pos) {
    if (it == tail_) throw std::invalid_argument("invalid pointer");
    it++;
  }
  if (it == head_)
    pop_front();
  else if (it == tail_)
    pop_back();
  else {
    Node<value_type> *node_prev = it.GetIt()->prev;
    Node<value_type> *node_next = it.GetIt()->next;
    delete it.it_;
    node_prev->next = node_next;
    node_next->prev = node_prev;
    size_--;
  }
}

template <class value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (other.size() == 0) return;
  if (size() == 0) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = 0;
  } else {
    iterator it = begin();
    while (it != pos) it++;
    if (it == head_) {
      other.tail_->next = head_;
      head_->prev = other.tail_;
      head_ = other.head_;
    } else if (it == tail_->next) {
      tail_->next = other.head_;
      other.head_->prev = tail_;
      tail_ = other.tail_;
    } else {
      Node<value_type> *node_prev = it.it_->prev;
      node_prev->next = other.head_;
      other.head_->prev = node_prev;
      other.tail_->next = it.it_;
      it.it_->prev = other.tail_;
    }
  }

  other.head_ = nullptr;
  other.tail_ = nullptr;
  size_ += other.size_;
  other.size_ = 0;
}

template <class value_type>
void list<value_type>::unique() {
  for (iterator it = begin() + 1; it != end(); it++) {
    if (*it == it.it_->prev->data) {
      erase(it.it_->prev);
    }
  }
}

template <class value_type>
void list<value_type>::sort() {
  if (size() > 1) {
    quick_sort(head_, tail_);
  }
}

template <class value_type>
void list<value_type>::quick_sort(iterator start, iterator end) {
  if (start > end || start == end || start == this->end() ||
      end == this->end() || start == tail_ ||
      (start.it_->next == nullptr && start.it_->prev == nullptr) ||
      (end.it_->next == nullptr && end.it_->prev == nullptr)) {
    return;
  }

  iterator p = partition(start, end);
  iterator p_dopl = p;
  quick_sort(start, p - 1);
  quick_sort(p_dopl + 1, end);
}

template <class value_type>
typename list<value_type>::iterator list<value_type>::partition(iterator start,
                                                                iterator end) {
  value_type pivot = end.it_->data;
  iterator pivot_index = start;

  for (iterator j = start; j != end; j++) {
    if (j.it_->data <= pivot) {
      std::swap(j.it_->data, pivot_index.it_->data);
      pivot_index++;
    }
  }
  std::swap(end.it_->data, pivot_index.it_->data);

  return pivot_index;
}

template <class value_type>
template <class... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    iterator pos, Args &&...args) {
  for (const auto &a : std::initializer_list<value_type>{args...}) {
    insert(pos, a);
  }
  pos--;
  return pos;
}

template <class value_type>
template <class... Args>
void list<value_type>::insert_many_back(Args &&...args) {
  for (const auto &a : std::initializer_list<value_type>{args...}) {
    push_back(a);
  }
}

template <class value_type>
template <class... Args>
void list<value_type>::insert_many_front(Args &&...args) {
  list<value_type> list;
  for (const auto &a : std::initializer_list<value_type>{args...}) {
    list.push_front(a);
  }
  while (!list.empty()) {
    push_front(list.front());
    list.pop_front();
  }
}

}  // namespace s21