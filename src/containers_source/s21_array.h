#ifndef __S21_ARRAY__
#define __S21_ARRAY__

#include "s21_containers_extra.h"

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef size_t size_type;

  array() { this->array_ = new value_type[N + 1](); }

  array(std::initializer_list<value_type> const& items) : array() {
    if (N < items.size()) throw "Invalid sizes (N < size)";

    for (size_type i = 0; i < items.size(); ++i)
      this->array_[i] = *(items.begin() + i);
  }

  array(const array& a) : array() {
    for (size_type i = 0; i < N; ++i) this->array_[i] = a.array_[i];
  }

  array(array&& a) {
    this->array_ = a.array_;
    a.array_ = nullptr;
  }

  ~array() { delete[] this->array_; }

  array operator=(array&& a) {
    this->~array();

    this->array_ = a.array_;
    a.array_ = nullptr;

    return *this;
  }

  array operator=(array& a) {
    for (size_type i = 0; i < a.size(); ++i) this->array_[i] = a.array_[i];

    return *this;
  }

  inline size_type size() { return N; }
  inline size_type max_size() { return (size_type)-1; }
  inline bool empty() { return !N; }

  iterator data() { return this->array_; }

  iterator begin() { return this->array_; }

  iterator end() {
    if (this->empty()) return this->array_;
    return this->array_ + N;
  }

  const_reference front() { return *this->array_; }

  const_reference back() {
    if (this->empty()) return *this->array_;
    return *(this->array_ + (N - 1));
  }

  reference at(size_type pos) {
    if (pos >= N) throw "Out of bounds";
    return this->array_[pos];
  }

  reference operator[](size_type pos) { return this->at(pos); }

  void swap(array& other) {
    value_type* temp_array = this->array_;
    this->array_ = other.array_;
    other.array_ = temp_array;
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < N; i++) this->array_[i] = value;
  }

  friend std::ostream& operator<<(std::ostream& os, array& a) {
    os << "{ ";
    for (auto i = a.begin(); i != a.end(); ++i) {
      if (i != a.begin()) os << ", ";
      os << *i;
    }
    os << " } (" << a.size() << ")";

    return os;
  }

 private:
  value_type* array_;
};
}  // namespace s21
#endif