namespace s21 {

template <class value_type, std::size_t N>
array<value_type, N>::array() : size_(N) {}

template <class value_type, std::size_t N>
array<value_type, N>::array(std::initializer_list<value_type> const &items)
    : size_(N) {
  if (N != items.size())
    throw std::invalid_argument("size of initializer_list not equal size!");
  int j = 0;
  for (value_type i : items) {
    array_elements_[j] = i;
    j++;
  }
}

template <class value_type, std::size_t N>
array<value_type, N>::array(const array &a) : size_(a.size_) {
  for (int i = 0; i < (int)size_; i++) {
    array_elements_[i] = a.array_elements_[i];
  }
}

template <class value_type, std::size_t N>
array<value_type, N>::array(array &&a) : size_(a.size_) {
  for (int i = 0; i < (int)size_; i++) {
    array_elements_[i] = a.array_elements_[i];
  }
  a.~array();
}

template <class value_type, std::size_t N>
typename array<value_type, N>::array array<value_type, N>::operator=(
    array &&a) noexcept {
  if (this == &a) {
    return *this;
  }
  size_ = a.size_;
  std::move(a.array_elements_, a.array_elements_ + size_, array_elements_);
  a.size_ = 0;
  std::fill_n(a.array_elements_, size_, 0);
  return *this;
}

template <class value_type, std::size_t N>
typename array<value_type, N>::array array<value_type, N>::operator=(
    const array &a) {
  if (this == &a) {
    return *this;
  }
  size_ = a.size_;
  for (int i = 0; i < (int)a.size_; i++) {
    array_elements_[i] = a.array_elements_[i];
  }
  return *this;
}

// for access elements
template <class value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::at(
    size_type pos) {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("out of range");
  }
  return array_elements_[pos];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::at(
    size_type pos) const {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("out of range");
  }
  return array_elements_[pos];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::operator[](
    size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("out of range");
  }
  return array_elements_[pos];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::operator[](
    size_type pos) const {
  if (pos < 0 || pos >= size_) {
    throw std::out_of_range("out of range");
  }
  return array_elements_[pos];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::front()
    const {
  return array_elements_[0];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::back()
    const {
  return array_elements_[size_ - 1];
}
template <class value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::front() {
  return array_elements_[0];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::back() {
  return array_elements_[size_ - 1];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::data() noexcept {
  return &array_elements_[0];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::begin() noexcept {
  return &array_elements_[0];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::const_iterator array<value_type, N>::begin()
    const noexcept {
  return &array_elements_[0];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::end() noexcept {
  return &array_elements_[size_];
}

template <class value_type, std::size_t N>
typename array<value_type, N>::const_iterator array<value_type, N>::end()
    const noexcept {
  return &array_elements_[size_];
}

// for access information about size
template <class value_type, std::size_t N>
bool array<value_type, N>::empty() const {
  return size_ == 0;
}

template <class value_type, std::size_t N>
typename array<value_type, N>::size_type array<value_type, N>::size() const {
  return size_;
}

template <class value_type, std::size_t N>
typename array<value_type, N>::size_type array<value_type, N>::max_size()
    const {
  return size();
}

// for change container
template <class value_type, std::size_t N>
void array<value_type, N>::swap(array &other) noexcept {
  array<value_type, N> a(other);
  for (int i = 0; i < (int)other.size(); i++) {
    other.array_elements_[i] = array_elements_[i];
  }
  for (int i = 0; i < (int)size(); i++) {
    array_elements_[i] = a.array_elements_[i];
  }
}

template <class value_type, std::size_t N>
void array<value_type, N>::fill(const_reference value) {
  for (int i = 0; i < (int)size(); i++) {
    array_elements_[i] = value;
  }
}

}  // namespace s21