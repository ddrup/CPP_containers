namespace s21 {

template <class value_type>
vector<value_type>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <class value_type>
vector<value_type>::vector(size_type n)
    : data_(new value_type[n]()), size_(n), capacity_(n) {}

template <class value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items)
    : data_(new value_type[items.size()]()),
      size_(items.size()),
      capacity_(items.size()) {
  int i = 0;
  for (value_type value : items) {
    data_[i] = value;
    i++;
  }
}
template <class value_type>
vector<value_type>::vector(const vector &v)
    : data_(new value_type[v.size()]()),
      size_(v.size()),
      capacity_(v.capacity_) {
  for (size_type i = 0; i < v.size(); i++) {
    data_[i] = v.data_[i];
  }
}
template <class value_type>
vector<value_type>::vector(vector &&v) {
  data_ = v.data_;
  size_ = v.size_;
  capacity_ = v.capacity_;
  v.size_ = 0;
  v.capacity_ = 0;
  v.data_ = nullptr;
}

template <class value_type>
vector<value_type>::~vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
}

template <class value_type>
vector<value_type> vector<value_type>::operator=(vector &&v) noexcept {
  if (this == &v) {
    return *this;
  }
  delete[] data_;
  data_ = v.data_;
  capacity_ = v.capacity_;
  size_ = v.size_;
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
  return *this;
}

template <class value_type>
vector<value_type> vector<value_type>::operator=(const vector &v) {
  if (this == &v) {
    return *this;
  }
  delete[] data_;
  data_ = new value_type[v.capacity_];
  size_ = v.size_;
  capacity_ = v.capacity_;
  for (size_type i = 0; i < v.size_; i++) {
    data_[i] = v.data_[i];
  }
  return *this;
}

template <class value_type>
bool vector<value_type>::empty() const noexcept {
  return size_ == 0;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::size()
    const noexcept {
  return size_;
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::max_size()
    const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <class value_type>
typename vector<value_type>::size_type vector<value_type>::capacity()
    const noexcept {
  return capacity_;
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::begin() noexcept {
  return iterator(data_);
}
template <class value_type>
typename vector<value_type>::iterator vector<value_type>::end() noexcept {
  return iterator(data_ + size_);
}

template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin()
    const noexcept {
  return const_iterator(data_);
}
template <class value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend()
    const noexcept {
  return const_iterator(data_ + size_);
}
template <class value_type>
void vector<value_type>::reserve(size_type size) {
  if (size <= capacity_) {
    return;
  }
  if (size > max_size()) {
    throw std::out_of_range("Errors!");
  }
  pointer new_data = new vector<value_type>::value_type[size];
  std::copy(data_, data_ + size_, new_data);
  delete[] data_;
  data_ = new_data;
  capacity_ = size;
}
template <class value_type>
void vector<value_type>::shrink_to_fit() {
  if (capacity_ == size_) {
    return;
  }
  value_type *new_data = new value_type[size_];
  std::copy(data_, data_ + size_, new_data);
  delete[] data_;
  data_ = new_data;
  capacity_ = size_;
}

template <class value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= size_ || size_ == 0) {
    throw std::out_of_range("Out of range");
  }
  return data_[pos];
}

template <class value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return data_[pos];
}

template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return data_[0];
}

template <class value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  return data_[size_ - 1];
}

template <class value_type>
value_type *vector<value_type>::data() {
  return data_;
}

template <class value_type>
void vector<value_type>::clear() {
  size_ = 0;
}

template <class value_type>
void vector<value_type>::push_back(const_reference value) {
  if (capacity_ <= size_) {
    reserve(size_ + 10);
  }
  size_++;
  data_[size_ - 1] = value;
}

template <class value_type>
void vector<value_type>::pop_back() {
  if (size_ != 0) {
    size_--;
  }
}

template <class value_type>
void vector<value_type>::swap(vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <class value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos == end()) {
    push_back(value);
    pos = end() - 1;
  } else {
    auto value1 = *pos;
    int i = 0;
    iterator it = begin();
    while (it != pos) {
      i++;
      it++;
    }
    *pos = value;
    pos++;
    while (pos != end()) {
      auto a = *pos;
      *pos = value1;
      value1 = a;
      pos++;
    }
    push_back(value1);
    pos = this->data_ + i;
  }
  return pos;
}

template <class value_type>
void vector<value_type>::erase(iterator pos) {
  if (pos == end() - 1) {
    *pos = 0;
  }
  iterator it = begin();
  while (it != pos) it++;
  it++;
  while (it != end()) {
    *pos = *it;
    pos++;
    it++;
  }
  *pos = 0;
  size_--;
}

template <class value_type>
template <class... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    iterator pos, Args &&...args) {
  int i = 0;
  iterator it = pos;
  for (const auto &a : std::initializer_list<value_type>{args...}) {
    if (i == 0) {
      it = insert(pos, a);
      pos = it;
    } else
      pos = insert(pos, a);
    pos++;
    i++;
  }
  return it;
}

template <class value_type>
template <class... Args>
void vector<value_type>::insert_many_back(Args &&...args) {
  for (const auto &a : std::initializer_list<value_type>{args...}) {
    push_back(a);
  }
}

}  // namespace s21
