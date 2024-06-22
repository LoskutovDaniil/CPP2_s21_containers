#ifndef __S21_QUEUE__
#define __S21_QUEUE__

#include "s21_containers_extra.h"

namespace s21 {
template <typename T>
class queue {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

  queue() {
    this->size_ = 0;
    this->root_ = new node_type(nullptr, nullptr, new value_type());
    this->root_->next = this->root_;
    this->root_->prev = this->root_;
  }

  queue(std::initializer_list<value_type> const& items) : queue() {
    for (size_type i = 0; i < items.size(); ++i)
      this->push(*(items.begin() + i));
  }

  queue(const queue& q) : queue() {
    if (!q.size_) return;

    value_type* values = new value_type[q.size_]();
    node_type* temp_node = q.root_->next;

    for (size_type i = 0; i < q.size_; ++i) {
      values[i] = *temp_node->value;
      temp_node = temp_node->next;
    }

    for (size_type i = 0; i < q.size_; ++i) {
      this->push(values[i]);
    }

    delete[] values;
  }

  queue(queue&& q) {
    this->root_ = q.root_;
    this->size_ = q.size_;

    q.root_ = nullptr;
    q.size_ = 0;
  }

  ~queue() {
    while (!this->empty()) this->pop();
    if (this->root_) {
      delete this->root_->value;
      delete this->root_;
    }
  }

  queue<value_type>& operator=(queue& q) {
    while (!this->empty()) this->pop();

    if (!q.size_) return *this;

    value_type* values = new value_type[q.size_]();
    node_type* temp_node = q.root_->next;

    for (size_type i = 0; i < q.size_; ++i) {
      values[i] = *temp_node->value;
      temp_node = temp_node->next;
    }

    for (size_type i = q.size_ - 1; i != ((size_type)-1); --i) {
      this->push(values[i]);
    }

    delete[] values;

    return *this;
  }

  queue<value_type>& operator=(queue&& q) {
    this->~queue();

    this->root_ = q.root_;
    this->size_ = q.size_;

    q.root_ = nullptr;
    q.size_ = 0;

    return *this;
  }

  inline const_reference front() { return *this->root_->next->value; }
  inline const_reference back() { return *this->root_->prev->value; }
  inline bool empty() { return !this->size_; }
  inline size_type size() { return this->size_; }

  void push(const_reference value) {
    node_type* new_node =
        new node_type(this->root_, this->root_->prev, new value_type(value));
    if (this->empty()) this->root_->next = new_node;
    this->root_->prev->next = new_node;
    this->root_->prev = new_node;
    this->size_++;
  }

  void pop() {
    if (this->empty()) return;

    node_type* temp_node = this->root_->next;

    this->root_->next = temp_node->next;
    this->root_->next->prev = this->root_;

    delete temp_node->value;
    delete temp_node;

    this->size_--;
  }

  void swap(queue& other) {
    node_type* temp_node = this->root_;
    size_type temp_size = this->size_;

    this->root_ = other.root_;
    this->size_ = other.size_;

    other.root_ = temp_node;
    other.size_ = temp_size;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return;

    value_type vargs[count_of_vargs] = {args...};
    for (size_type i = 0; i < count_of_vargs; ++i) {
      this->push(vargs[i]);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, queue<value_type>& l) {
    os << "{ ";
    s21::queue<value_type> tmp = s21::queue<value_type>(l);
    s21::queue<value_type>::size_type tmp_size = tmp.size();
    for (size_t i = 0; i < tmp_size; ++i) {
      os << tmp.front();
      tmp.pop();
      if (i + 1 < tmp_size) os << ", ";
    }
    os << " } (" << l.size() << ")";
    return os;
  }

 private:
  typedef Node<value_type> node_type;

  node_type* root_;
  size_type size_;
};
}  // namespace s21
#endif