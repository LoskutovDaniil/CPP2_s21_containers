#ifndef __S21_MULTISET__
#define __S21_MULTISET__

#include "s21_containers_extra.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class multiset {
 protected:
  typedef BinaryNodeT<Key> node_type;

 public:
  typedef Key key_type;
  typedef key_type value_type;

  typedef key_type& reference;
  typedef const key_type& const_reference;
  typedef size_t size_type;

  template <typename T>
  class MultisetIterator : public BinaryIteratorT<key_type> {
   public:
    MultisetIterator() {}
    MultisetIterator(node_type* node) : BinaryIteratorT<key_type>(node) {}

    MultisetIterator<key_type>& operator++() {
      if (!this->node->parent) {
        if (this->node->right) {
          this->node = this->node->right;
          while (this->node->left) this->node = this->node->left;
        }
        return *this;
      }

      node_type* parent_node = this->node;

      if (parent_node->right) {
        parent_node = parent_node->right;
        while (parent_node->left) parent_node = parent_node->left;
      } else {
        key_type this_key = *this->node->value;
        while (parent_node->parent && *parent_node->value <= this_key)
          parent_node = parent_node->parent;
      }

      this->node = parent_node;
      return *this;
    }

    MultisetIterator<key_type>& operator--() {
      if (!this->node->parent) {
        if (this->node->right) {
          this->node = this->node->right;
          while (this->node->right) this->node = this->node->right;
        }
        return *this;
      }

      node_type* parent_node = this->node;

      if (parent_node->left) {
        parent_node = parent_node->left;
        while (parent_node->right) parent_node = parent_node->right;
      } else {
        key_type this_key = *this->node->value;
        while (parent_node->parent && *parent_node->value >= this_key)
          parent_node = parent_node->parent;
      }

      this->node = parent_node;
      return *this;
    }

    MultisetIterator<key_type> operator++(int) {
      iterator i = *this;
      ++(*this);
      return i;
    }

    MultisetIterator<key_type> operator--(int) {
      iterator i = *this;
      --(*this);
      return i;
    }

    MultisetIterator<key_type> operator+(int step) {
      MultisetIterator<key_type> tmp = *this;
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? ++(tmp) : --(tmp);
      }
      return tmp;
    }

    MultisetIterator<key_type> operator-(int step) {
      MultisetIterator<key_type> tmp = *this;
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? --(tmp) : ++(tmp);
      }
      return tmp;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    MultisetIterator<key_type>& i) {
      os << (*i);

      return os;
    }
  };

  typedef MultisetIterator<key_type> iterator;

  template <typename T>
  class MultisetConstIterator : public MultisetIterator<key_type> {
   public:
    MultisetConstIterator() {}

    MultisetConstIterator(node_type* node) : MultisetIterator<key_type>(node) {}

    MultisetConstIterator(const MultisetIterator<key_type>& obj) {
      this->node = obj.node;
    }

    const_reference& operator*() { return (const T&)*this->node->value; }
  };

  typedef MultisetConstIterator<key_type> const_iterator;

  multiset() {
    this->root_ = new node_type();
    this->size_ = 0;
  }

  multiset(std::initializer_list<key_type> const& items) : multiset() {
    for (size_t i = 0; i < items.size(); ++i) {
      key_type new_value = *(items.begin() + i);
      this->insert(new_value);
    }
  }

  multiset(const multiset& m) : multiset() {
    for (iterator i = ((multiset&)m).begin(); i != ((multiset&)m).end(); ++i) {
      this->insert(*i);
    }
  }

  multiset(multiset&& m) {
    this->root_ = m.root_;
    this->size_ = m.size_;

    m.root_ = nullptr;
    m.size_ = 0;
  }

  ~multiset() {
    if (this->root_) {
      this->clear();
      delete this->root_->value;
      delete this->root_;
    }
  }

  multiset operator=(multiset&& m) {
    this->~multiset();

    this->root_ = m.root_;
    this->size_ = m.size_;

    m.root_ = nullptr;
    m.size_ = 0;

    return *this;
  }

  multiset operator=(std::initializer_list<key_type> const& items) {
    this->clear();
    for (size_t i = 0; i < items.size(); i++) {
      key_type new_value = *(items.begin() + i);
      this->insert(new_value);
    }

    return *this;
  }

  inline bool empty() { return !this->size_; }
  inline size_type max_size() { return (size_type)-1; }
  inline size_type size() { return this->size_; }

  iterator insert(const_reference value) {
    if (this->empty()) {
      this->root_->right = new node_type(this->root_, value);
      this->size_++;
      return iterator(this->root_->right);
    }

    node_type* parent_node = this->root_->right;
    bool left_direction = value < *parent_node->value;

    while (left_direction ? parent_node->left : parent_node->right) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = value < *parent_node->value;
    }

    node_type* result_node = parent_node;

    node_type* new_node = new node_type(parent_node, value);
    left_direction ? (parent_node->left = new_node)
                   : (parent_node->right = new_node);
    result_node = new_node;
    this->size_++;

    return iterator(result_node);
  }

  iterator begin() {
    if (this->empty()) return this->end();

    node_type* temp_node = this->root_->right;
    while (temp_node->left) temp_node = temp_node->left;

    return iterator(temp_node);
  }

  inline iterator end() { return iterator(this->root_); }

  void clear() {
    node_type** nodes = new node_type*[this->size_]();
    size_type j = 0;
    for (iterator i = this->begin(); i != this->end(); ++i, ++j) {
      nodes[j] = i.node;
    }

    for (j = 0; j < this->size_; ++j) {
      delete nodes[j]->value;
      delete nodes[j];
    }

    delete[] nodes;
    this->size_ = 0;
  }

  void erase(iterator pos) {
    if (pos == this->end()) return;

    this->size_--;

    if (!pos.node->right) {
      node_type* parent_node = pos.node->parent;
      bool left_direction = parent_node->left == pos.node;

      delete pos.node->value;
      delete pos.node;

      left_direction ? parent_node->left = nullptr
                     : parent_node->right = nullptr;
      return;
    }

    node_type* root_node = pos.node;
    node_type* temp_node = root_node->right;
    node_type* left_node = root_node->left;

    bool left_direction = root_node->parent->left == pos.node;

    left_direction ? root_node->parent->left = root_node->right
                   : root_node->parent->right = root_node->right;
    temp_node->parent = root_node->parent;

    delete root_node->value;
    delete root_node;

    while (temp_node->left) temp_node = temp_node->left;
    temp_node->left = left_node;
    if (left_node) left_node->parent = temp_node;
  }

  void merge(multiset& other) {
    for (iterator i = other.begin(); i != other.end(); ++i) {
      this->insert(*i.node->value);
    }

    other.clear();
  }

  void swap(multiset& other) {
    node_type* temp_root = this->root_;
    size_type temp_size = this->size_;

    this->root_ = other.root_;
    this->size_ = other.size_;

    other.root_ = temp_root;
    other.size_ = temp_size;
  }

  bool contains(const Key& key) {
    if (this->empty()) return false;

    node_type* parent_node = this->root_->right;
    bool left_direction = key < *parent_node->value;
    bool result = (key == *parent_node->value);

    while (!result &&
           (left_direction ? parent_node->left : parent_node->right)) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = key < *parent_node->value;
      result = key == *parent_node->value;
    }

    return result;
  }

  iterator find(const Key& key) {
    if (this->empty()) return this->end();

    node_type* parent_node = this->root_->right;
    bool left_direction = key < *parent_node->value;
    bool result = (key == *parent_node->value);

    while (!result &&
           (left_direction ? parent_node->left : parent_node->right)) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = key < *parent_node->value;
      result = key == *parent_node->value;
    }

    if (result)
      return iterator(parent_node);
    else
      return this->end();
  }

  size_type count(const Key& key) {
    size_type result = 0;

    iterator iter = this->find(key);
    if (iter != this->end()) {
      result = 1;
      while (*(++iter) == key) ++result;
    }

    return result;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    std::pair<iterator, iterator> result =
        std::pair<iterator, iterator>(this->end(), this->end());

    size_type count_of_keys = this->count(key);
    if (count_of_keys) {
      result.first = this->find(key);
      result.second = result.first + count_of_keys;
    }

    return result;
  }

  iterator lower_bound(const Key& key) {
    iterator result = this->end();

    for (iterator i = this->begin(); i != this->end() && result == this->end();
         ++i) {
      if (*i >= key) result = i;
    }

    return result;
  }

  iterator upper_bound(const Key& key) {
    iterator result = this->end();

    for (iterator i = this->begin(); i != this->end() && result == this->end();
         ++i) {
      if (*i > key) result = i;
    }

    return result;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> result =
        s21::vector<std::pair<iterator, bool>>();
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return result;

    value_type vargs[count_of_vargs] = {args...};

    for (size_type i = 0; i < count_of_vargs; ++i) {
      result.push_back(std::pair(this->insert(vargs[i]), true));
    }

    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, multiset<key_type>& s) {
    os << "{";
    for (auto i = s.begin(); i != s.end(); ++i) {
      if (i != s.begin()) os << ", ";
      os << i;
    }
    os << "} (" << s.size() << ")";

    return os;
  }

 private:
  node_type* root_;
  size_type size_;
};
}  // namespace s21

#endif