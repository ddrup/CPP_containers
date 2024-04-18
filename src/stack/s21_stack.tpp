namespace s21 {

template <class T, class Container>
stack<T, Container>::stack() : list_() {}

template <class T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items)
    : list_(items) {}

template <class T, class Container>
stack<T, Container>::stack(const stack &s) : list_(s.lis_) {}

template <class T, class Container>
stack<T, Container>::stack(stack &&s) : list_(std::move(s.list_)) {}

template <class T, class Container>
stack<T, Container>::~stack() {
  while (!list_.empty()) {
    list_.pop_back();
  }
}

template <class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(stack const &s) {
  if (this != &s) {
    this->list_ = s.list_;
  }
  return *this;
}

template <class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(stack &&s) noexcept {
  if (this != &s) {
    this->list_ = std::move(s.list_);
  }
  return *this;
}

template <class T, class Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() {
  return list_.back();
}

template <class T, class Container>
bool stack<T, Container>::empty() {
  return list_.empty();
}

template <class T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() {
  return list_.size();
}

template <class T, class Container>
void stack<T, Container>::push(const_reference value) {
  list_.push_back(value);
}

template <class T, class Container>
void stack<T, Container>::pop() {
  list_.pop_back();
}

template <class T, class Container>
void stack<T, Container>::swap(stack &other) {
  list_.swap(other.list_);
}

template <class T, class Container>
template <class... Args>
void stack<T, Container>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}
}  // namespace s21