#ifndef __S21_LIST__
#define __S21_LIST__

#include "s21_containers_extra.h"

namespace s21 {
template <typename T>
class list {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

  template <typename T1>
  class ListIterator : public Iterator<value_type> {
   public:
    ListIterator() {}
    ListIterator(Node<value_type>* node) : Iterator<value_type>(node) {}

    ListIterator<value_type>& operator++() {
      this->node = this->node->next;
      return *this;
    }

    ListIterator<value_type>& operator--() {
      this->node = this->node->prev;
      return *this;
    }

    ListIterator<value_type> operator++(int) {
      iterator i = *this;
      ++(*this);
      return i;
    }

    ListIterator<value_type> operator--(int) {
      iterator i = *this;
      this->node = this->node->prev;
      return i;
    }

    ListIterator<value_type>& operator+(int step) {
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? ++(*this) : --(*this);
      }
      return *this;
    }

    ListIterator<value_type>& operator-(int step) {
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? --(*this) : ++(*this);
      }
      return *this;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    ListIterator<value_type> i) {
      os << *i;
      return os;
    }
  };

  template <typename T1>
  class ListConstIterator : public ListIterator<value_type> {
   public:
    Node<value_type>* node;
    ListConstIterator(Node<value_type>* node)
        : ListIterator<value_type>(node) {}
    ListConstIterator(const ListIterator<value_type>& obj) { node = obj.node; }

    const_reference operator*() { return *(this->node->value); }
  };

  typedef ListIterator<value_type> iterator;
  typedef ListConstIterator<value_type> const_iterator;

  list() {
    this->front_ = new Node<value_type>;
    this->front_->next = this->front_;
    this->front_->prev = this->front_;
    this->front_->value = new value_type();
    this->back_ = this->front_;
    this->back_->next = this->back_;
    this->back_->prev = this->back_;
    this->size_ = 0;
  }

  list(size_type n) : list() {
    for (size_type i = 0; i < n; i++) {
      this->push_back(0);
    }
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (size_t i = 0; i < items.size(); i++) {
      value_type new_value = *(items.begin() + i);
      this->push_back(new_value);
    }
  }

  list(const list& l) : list() {
    for (iterator i = ((list&)l).begin(); i != ((list&)l).end(); ++i) {
      this->push_back(*i);
    }
  }

  list(list&& l) {
    this->back_ = l.back_;
    this->front_ = l.front_;
    this->size_ = l.size_;

    l.back_ = nullptr;
    l.front_ = nullptr;
    l.size_ = 0;
  }

  ~list() {
    this->clear();
    if (this->front_) {
      delete this->front_->value;
      delete this->front_;
    }
  }

  list operator=(std::initializer_list<value_type> const& items) {
    this->clear();
    for (size_t i = 0; i < items.size(); i++) {
      value_type new_value = *(items.begin() + i);
      this->push_back(new_value);
    }

    return *this;
  }

  list operator=(list& l) {
    if (this == &l) return *this;
    this->clear();

    for (iterator i = l.begin(); i != l.end(); ++i) {
      this->push_back(*i);
    }

    return *this;
  }

  list operator=(list&& l) {
    if (this == &l) return *this;
    this->~list();

    this->back_ = l.back_;
    this->front_ = l.front_;
    this->size_ = l.size_;

    l.back_ = nullptr;
    l.front_ = nullptr;
    l.size_ = 0;

    return *this;
  }

  inline const_reference front() { return *this->front_->next->value; };
  inline const_reference back() { return *this->back_->value; };

  inline iterator begin() { return iterator(this->front_->next); }
  inline iterator end() { return iterator(this->back_->next); }

  inline bool empty() { return !this->size_; };
  inline size_type size() { return this->size_; }
  inline size_type max_size() { return (size_type)-1; };

  void clear() {
    while (this->size_ > 0) {
      Node<value_type>* next = this->front_->next;
      delete this->front_->value;
      delete this->front_;
      this->front_ = next;
      this->size_--;
    }
  }

  iterator insert(iterator pos, const_reference value) {
    Node<value_type>* node = pos.node;
    Node<value_type>* new_node = new Node<value_type>;
    node->prev->next = new_node;
    new_node->prev = node->prev;
    new_node->next = node;
    new_node->value = new value_type();
    *(new_node->value) = value;

    node->prev = new_node;
    this->size_++;
    return --pos;
  }

  void erase(iterator pos) {
    if (this->empty()) return;

    iterator p = pos;
    Node<value_type>* node = pos.node;
    if ((++p) != this->end()) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    } else
      this->back_ = node->prev;

    delete node->value;
    delete node;

    this->size_--;
  }

  void push_back(const_reference value) {
    Node<value_type>* back_node = this->back_;
    this->back_ = new Node<value_type>;
    back_node->next = this->back_;
    this->back_->next = this->front_;
    this->back_->prev = back_node;
    this->front_->prev = this->back_;
    this->back_->value = new value_type();
    *(this->back_->value) = value;
    this->size_++;
  }

  inline void pop_back() { this->erase(--(this->end())); }

  void push_front(const_reference value) {
    if (this->empty()) {
      this->push_back(value);
      return;
    }

    Node<value_type>* front_node = new Node<value_type>;
    front_node->value = new value_type();
    *(front_node->value) = value;
    this->size_++;

    Node<value_type>* next_node = this->front_->next;
    this->front_->next->prev = front_node;
    this->front_->next = front_node;

    front_node->prev = this->front_;
    front_node->next = next_node;
  }

  inline void pop_front() { this->erase(this->begin()); }

  void swap(list& other) {
    list<value_type> temp = list<value_type>(*this);
    this->clear();
    for (iterator i = other.begin(); i != other.end(); ++i) {
      this->push_back(*i);
    }

    other = temp;
  }

  void merge(list& other) {
    for (iterator i = other.begin(); i != other.end(); ++i) {
      this->push_back(*i);
    }

    this->sort();
  }

  void splice(const_iterator pos, __attribute_maybe_unused__ list& other) {
    list<value_type> temp = list<value_type>();
    iterator i_pos = iterator();
    i_pos.node = pos.node;
    for (iterator i = this->begin(); i != i_pos; ++i) {
      temp.push_back(*i);
    }

    for (iterator i = other.begin(); i != other.end(); ++i) {
      temp.push_back(*i);
    }

    for (iterator i = i_pos; i != this->end(); ++i) {
      temp.push_back(*i);
    }

    *this = temp;
  }

  void reverse() {
    list<value_type> temp = list<value_type>();
    iterator i = this->end();

    do {
      --i;
      temp.push_back(*i);
    } while (i != this->begin());

    *this = temp;
  }

  void unique() {
    if (this->size() < 2) return;

    iterator i = this->begin();
    ++i;
    do {
      iterator prev_i = --i;
      iterator this_i = ++i;
      if (*prev_i == *this_i) this->erase(prev_i);
    } while ((++i).node != this->end().node->next);
  }

  void sort() {
    list<value_type> temp = list<value_type>();
    while (!this->empty()) {
      iterator minimum = this->begin();
      iterator i = this->begin();
      ++i;
      for (; i != this->end(); ++i) {
        if (*i <= *minimum) minimum = i;
      }
      temp.push_back(*minimum);
      this->erase(minimum);
    }

    *this = temp;
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator iter = iterator(pos.node);
    bool is_end = iter == this->end();
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return iter;

    value_type vargs[count_of_vargs] = {args...};
    for (size_type i = 0; i < count_of_vargs; ++i) {
      if (is_end)
        this->push_back(vargs[i]);
      else
        this->insert(iter, vargs[i]);
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

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return;

    value_type vargs[count_of_vargs] = {args...};
    for (size_type i = count_of_vargs - 1; i != (size_type)-1; --i) {
      this->push_front(vargs[i]);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, list<value_type>& l) {
    os << "{ ";
    for (iterator i = l.begin(); i != l.end(); ++i) {
      os << *i << " ";
    }
    os << "} (" << l.size() << ")";
    return os;
  }

 private:
  Node<value_type>* front_;
  Node<value_type>* back_;
  size_type size_;
};
}  // namespace s21

#endif
