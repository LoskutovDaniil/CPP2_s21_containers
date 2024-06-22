#ifndef __S21_SET__
#define __S21_SET__

#include "s21_containers_extra.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set {
 protected:
  typedef BinaryNodeT<Key> node_type;

 public:
  typedef Key key_type;
  typedef key_type value_type;

  typedef key_type& reference;
  typedef const key_type& const_reference;
  typedef size_t size_type;

  template <typename T>
  class SetIterator : public BinaryIteratorT<key_type> {
   public:
    SetIterator() {}
    SetIterator(node_type* node) : BinaryIteratorT<key_type>(node) {}

    SetIterator<key_type>& operator++() {
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

    SetIterator<key_type>& operator--() {
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

    SetIterator<key_type> operator++(int) {
      iterator i = *this;
      ++(*this);
      return i;
    }

    SetIterator<key_type> operator--(int) {
      iterator i = *this;
      --(*this);
      return i;
    }

    SetIterator<key_type> operator+(int step) {
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? ++(*this) : --(*this);
      }
      return *this;
    }

    SetIterator<key_type> operator-(int step) {
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? --(*this) : ++(*this);
      }
      return *this;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    SetIterator<key_type>& i) {
      os << (*i);

      return os;
    }
  };

  typedef SetIterator<key_type> iterator;

  template <typename T>
  class SetConstIterator : public SetIterator<key_type> {
   public:
    SetConstIterator() {}

    SetConstIterator(node_type* node) : SetIterator<key_type>(node) {}

    SetConstIterator(const SetIterator<key_type>& obj) {
      this->node = obj.node;
    }

    const_reference& operator*() { return (const T&)*this->node->value; }
  };

  typedef SetConstIterator<key_type> const_iterator;

  set() {
    this->root_ = new node_type();
    this->size_ = 0;
  }

  set(std::initializer_list<key_type> const& items) : set() {
    for (size_t i = 0; i < items.size(); ++i) {
      key_type new_value = *(items.begin() + i);
      this->insert(new_value);
    }
  }

  set(const set& m) : set() {
    for (iterator i = ((set&)m).begin(); i != ((set&)m).end(); ++i) {
      this->insert(*i);
    }
  }

  set(set&& m) {
    this->root_ = m.root_;
    this->size_ = m.size_;

    m.root_ = nullptr;
    m.size_ = 0;
  }

  ~set() {
    if (this->root_) {
      this->clear();
      delete this->root_->value;
      delete this->root_;
    }
  }

  set operator=(set&& m) {
    this->~set();

    this->root_ = m.root_;
    this->size_ = m.size_;

    m.root_ = nullptr;
    m.size_ = 0;

    return *this;
  }

  set operator=(std::initializer_list<key_type> const& items) {
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

  std::pair<iterator, bool> insert(const_reference value) {
    if (this->empty()) {
      this->root_->right = new node_type(this->root_, value);
      this->size_++;
      return std::pair<iterator, bool>(iterator(this->root_->right), true);
    }

    node_type* parent_node = this->root_->right;
    bool left_direction = value < *parent_node->value;
    bool good = value != *parent_node->value;

    while (good && (left_direction ? parent_node->left : parent_node->right)) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = value < *parent_node->value;
      good = value != *parent_node->value;
    }

    node_type* result_node = parent_node;

    if (good) {
      node_type* new_node = new node_type(parent_node, value);
      left_direction ? (parent_node->left = new_node)
                     : (parent_node->right = new_node);
      result_node = new_node;
      this->size_++;
    }

    return std::pair<iterator, bool>(iterator(result_node), good);
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

  void merge(set& other) {
    size_type out_i = 0, out_j = 0;

    node_type** out_nodes =
        (node_type**)calloc(other.size_, sizeof(node_type*));
    key_type** out_values = (key_type**)calloc(out_j, sizeof(key_type*));

    for (iterator i = other.begin(); i != other.end(); ++i) {
      std::pair<iterator, bool> result = this->insert(*i.node->value);

      out_nodes[out_i++] = i.node;

      if (result.second) {
        delete result.first.node->value;
        result.first.node->value = i.node->value;
      } else {
        out_values =
            (key_type**)realloc(out_values, sizeof(key_type*) * (out_j + 1));
        out_values[out_j++] = i.node->value;
      }
    }

    for (size_type i = 0; i < out_i; ++i) delete out_nodes[i];
    for (size_type i = 0; i < out_j; ++i) delete out_values[i];

    free(out_nodes);
    free(out_values);

    other.root_->right = nullptr;
    other.size_ = 0;
  }

  void swap(set& other) {
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

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> result =
        s21::vector<std::pair<iterator, bool>>();
    const size_type count_of_vargs = sizeof...(args);
    if (!count_of_vargs) return result;

    value_type vargs[count_of_vargs] = {args...};

    for (size_type i = 0; i < count_of_vargs; ++i) {
      result.push_back(this->insert(vargs[i]));
    }

    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, set<key_type>& s) {
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