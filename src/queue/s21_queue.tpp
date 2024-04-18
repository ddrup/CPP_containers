namespace s21 {

template <class T, class Container>
queue<T, Container>::queue() : list_() {}

template <class T, class Container>
queue<T, Container>::queue(std::initializer_list<value_type> const &items)
    : list_(items) {}

template <class T, class Container>
queue<T, Container>::queue(const queue &s) : list_(s.list_) {}

template <class T, class Container>
queue<T, Container>::queue(queue &&s) : list_(std::move(s.list_)) {}

template <class T, class Container>
queue<T, Container>::~queue() {
  while (!list_.empty()) {
    list_.pop_front();
  }
}

template <class T, class Container>
queue<T, Container> &queue<T, Container>::operator=(queue const &s) {
  if (this != &s) {
    this->list_ = s.list_;
  }
  return *this;
}

template <class T, class Container>
queue<T, Container> &queue<T, Container>::operator=(queue &&s) noexcept {
  if (this != &s) {
    this->list_ = std::move(s.list_);
  }
  return *this;
}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::front() {
  return list_.front();
}

template <class T, class Container>
typename queue<T, Container>::const_reference queue<T, Container>::back() {
  return list_.back();
}

template <class T, class Container>
bool queue<T, Container>::empty() {
  return list_.empty();
}

template <class T, class Container>
typename queue<T, Container>::size_type queue<T, Container>::size() {
  return list_.size();
}

template <class T, class Container>
void queue<T, Container>::push(const_reference value) {
  list_.push_back(value);
}

template <class T, class Container>
void queue<T, Container>::pop() {
  list_.pop_front();
}

template <class T, class Container>
void queue<T, Container>::swap(queue &other) {
  list_.swap(other.list_);
}

template <class T, class Container>
template <class... Args>
void queue<T, Container>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

}  // namespace s21