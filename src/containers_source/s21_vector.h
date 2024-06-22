#ifndef __S21_VECTOR__
#define __S21_VECTOR__

#include "s21_containers_extra.h"

namespace s21 {
template <typename T>
class vector {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef size_t size_type;

  vector() {
    this->size_ = 0;
    this->capacity_ = 0;
    this->array_ = new value_type[1]();
  }

  vector(size_type n) {
    this->size_ = n;
    this->capacity_ = n;
    this->array_ = new value_type[1 + n]();
  }

  vector(std::initializer_list<value_type> const& items)
      : vector(items.size()) {
    for (size_type i = 0; i < items.size(); ++i) {
      this->array_[i] = *(items.begin() + i);
    }
  }

  vector(const vector& v) : vector(v.size_) {
    for (size_type i = 0; i < v.size_; ++i) {
      this->array_[i] = v.array_[i];
    }
  }

  vector(vector&& v) {
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->array_ = v.array_;

    v.size_ = 0;
    v.capacity_ = 0;
    v.array_ = nullptr;
  }

  ~vector() {
    delete[] this->array_;
    this->size_ = 0;
    this->capacity_ = 0;
  }

  vector& operator=(vector&& v) {
    this->~vector();

    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->array_ = v.array_;

    v.size_ = 0;
    v.capacity_ = 0;
    v.array_ = nullptr;

    return *this;
  }

  vector& operator=(const vector& v) {
    vector<value_type> temp = vector<value_type>(v);
    *this = (vector<value_type> &&) temp;

    return *this;
  }

  inline value_type* data() { return this->array_; }

  inline bool empty() { return !this->size_; }

  inline size_type max_size() { return (size_type)-1; }

  inline size_type size() { return this->size_; }

  inline size_type capacity() { return this->capacity_; }

  inline const_reference front() { return *this->array_; }

  inline const_reference back() {
    if (this->empty()) return *this->array_;
    return *(this->array_ + (this->size_ - 1));
  }

  inline iterator begin() { return this->array_; }

  inline iterator end() {
    if (this->empty()) return this->array_;
    return this->array_ + this->size_;
  }

  inline reference operator[](size_type pos) { return this->at(pos); }

  inline reference at(size_type pos) {
    if (this->empty()) return *this->array_;
    if (this->size_ <= pos)
      throw "Out of range";
    else
      return this->array_[pos];
  }

  void reserve(size_type size) {
    if (size <= this->capacity_) return;

    value_type* new_array = new value_type[size + 1]();
    for (size_type i = 0; i < this->size_; ++i) {
      new_array[i] = this->array_[i];
    }

    delete[] this->array_;
    this->array_ = new_array;
    this->capacity_ = size;
  }

  void shrink_to_fit() {
    if (this->size_ == this->capacity_) return;

    value_type* new_array = new value_type[this->size_ + 1]();
    for (size_type i = 0; i < this->size_; ++i) new_array[i] = this->array_[i];

    delete[] this->array_;

    this->array_ = new_array;
    this->capacity_ = this->size_;
  }

  void clear() {
    delete[] this->array_;

    this->size_ = 0;
    this->capacity_ = 0;
    this->array_ = new value_type[1]();
  }

  iterator insert(iterator pos, const_reference value) {
    size_type pos_index = pos - this->array_;

    this->reserve(this->size_ + 1);
    pos = this->array_ + pos_index;

    for (iterator i = this->end(); i != pos; --i) *i = *(i - 1);
    *pos = value;

    ++this->size_;
    return pos;
  }

  void erase(iterator pos) {
    if (pos >= this->end()) throw "Out of range";
    if (this->empty()) return;

    for (iterator i = pos; i != this->end(); ++i) *i = *(i + 1);

    this->size_--;
  }

  void push_back(const_reference value) {
    this->reserve(this->size_ + 1);

    *this->end() = value;

    this->size_++;
  }

  void pop_back() {
    if (this->empty()) return;

    this->array_[--this->size_] = 0;
  }

  void swap(vector& other) {
    size_type temp_size = this->size_;
    size_type temp_capacity = this->capacity_;
    value_type* temp_array = this->array_;

    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    this->array_ = other.array_;

    other.size_ = temp_size;
    other.capacity_ = temp_capacity;
    other.array_ = temp_array;
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return (iterator)pos;

    iterator iter = (iterator)pos;

    value_type vargs[count_of_vargs] = {args...};
    for (size_type i = 0; i < count_of_vargs; ++i) {
      iter = this->insert(iter, vargs[i]) + 1;
    }

    return iter;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return;

    value_type vargs[count_of_vargs] = {args...};
    for (size_type i = 0; i < count_of_vargs; ++i) {
      this->push_back(vargs[i]);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, vector& v) {
    os << "{ ";
    for (auto i = v.begin(); i != v.end(); ++i) {
      if (i != v.begin()) os << ", ";
      os << *i;
    }
    os << " } (" << v.size() << ") (" << v.capacity() << ")";

    return os;
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type* array_;
};
}  // namespace s21
#endif