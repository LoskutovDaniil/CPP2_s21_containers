#ifndef __S21_MAP__
#define __S21_MAP__

#include "s21_containers_extra.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef BinaryNode<key_type, mapped_type> node_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;

  template <typename T1, typename T2>
  class MapIterator : public BinaryIterator<key_type, mapped_type> {
   public:
    MapIterator() {}
    MapIterator(node_type* node)
        : BinaryIterator<key_type, mapped_type>(node) {}

    MapIterator<key_type, mapped_type>& operator++() {
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
        key_type this_key = this->node->value->first;
        while (parent_node->parent && parent_node->value->first <= this_key)
          parent_node = parent_node->parent;
      }

      this->node = parent_node;
      return *this;
    }

    MapIterator<key_type, mapped_type>& operator--() {
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
        key_type this_key = this->node->value->first;
        while (parent_node->parent && parent_node->value->first >= this_key)
          parent_node = parent_node->parent;
      }

      this->node = parent_node;
      return *this;
    }

    MapIterator<key_type, mapped_type> operator++(int) {
      iterator i = *this;
      ++(*this);
      return i;
    }

    MapIterator<key_type, mapped_type> operator--(int) {
      iterator i = *this;
      --(*this);
      return i;
    }

    MapIterator<key_type, mapped_type> operator+(int step) {
      MapIterator<key_type, mapped_type> tmp = *this;
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? ++(tmp) : --(tmp);
      }
      return tmp;
    }

    MapIterator<key_type, mapped_type> operator-(int step) {
      MapIterator<key_type, mapped_type> tmp = *this;
      for (int i = 0; i != step; step > 0 ? ++i : --i) {
        step > 0 ? --(tmp) : ++(tmp);
      }
      return tmp;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    MapIterator<key_type, mapped_type>& i) {
      os << "{" << (*i).first << ": " << (*i).second << "}";

      return os;
    }
  };

  typedef MapIterator<key_type, mapped_type> iterator;

  template <typename T1, typename T2>
  class MapConstIterator : public MapIterator<key_type, mapped_type> {
   public:
    MapConstIterator() {}

    MapConstIterator(node_type* node)
        : MapIterator<key_type, mapped_type>(node) {}

    MapConstIterator(const MapIterator<key_type, mapped_type>& obj) {
      this->node = obj.node;
    }

    const_reference& operator*() {
      return (std::pair<const T1, T2>&)*this->node->value;
    }
  };

  typedef MapConstIterator<key_type, mapped_type> const_iterator;

  map() {
    this->size_ = 0;
    this->root_ = new node_type();
  }

  map(std::initializer_list<value_type> const& items) : map() {
    for (size_t i = 0; i < items.size(); ++i) {
      value_type new_value = *(items.begin() + i);
      this->insert(new_value);
    }
  }

  map(const map& m) : map() {
    for (iterator i = ((map&)m).begin(); i != ((map&)m).end(); ++i) {
      this->insert(*i);
    }
  }

  map(map&& m) {
    this->root_ = m.root_;
    this->size_ = m.size_;

    m.root_ = nullptr;
    m.size_ = 0;
  }

  ~map() {
    if (this->root_) {
      this->clear();
      delete this->root_->value;
      delete this->root_;
    }
  }

  map operator=(map&& m) {
    this->~map();

    this->root_ = m.root_;
    this->size_ = m.size_;

    m.root_ = nullptr;
    m.size_ = 0;

    return *this;
  }

  map operator=(std::initializer_list<value_type> const& items) {
    this->clear();
    for (size_t i = 0; i < items.size(); i++) {
      value_type new_value = *(items.begin() + i);
      this->insert(new_value);
    }

    return *this;
  }

  iterator begin() {
    if (this->empty()) return this->end();
    node_type* temp_node = this->root_->right;
    while (temp_node->left) temp_node = temp_node->left;

    return iterator(temp_node);
  }

  inline iterator end() { return iterator(this->root_); }

  inline bool empty() { return !this->size_; }
  inline size_type max_size() { return (size_type)-1; }
  inline size_type size() { return this->size_; }

  std::pair<iterator, bool> insert(const_reference value) {
    if (this->empty()) {
      this->root_->right =
          new node_type(this->root_, value.first, value.second);
      this->size_++;
      return std::pair<iterator, bool>(iterator(this->root_->right), true);
    }

    node_type* parent_node = this->root_->right;
    bool left_direction = value.first < parent_node->value->first;
    bool good = value.first != parent_node->value->first;

    while (good && (left_direction ? parent_node->left : parent_node->right)) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = value.first < parent_node->value->first;
      good = value.first != parent_node->value->first;
    }

    node_type* result_node = parent_node;

    if (good) {
      node_type* new_node =
          new node_type(parent_node, value.first, value.second);
      left_direction ? (parent_node->left = new_node)
                     : (parent_node->right = new_node);
      result_node = new_node;
      this->size_++;
    }

    return std::pair<iterator, bool>(iterator(result_node), good);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& obj) {
    std::pair<key_type, mapped_type> value =
        std::pair<key_type, mapped_type>(key, obj);
    return this->insert(value);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    if (this->empty()) {
      this->root_->right = new node_type(this->root_, key, obj);
      this->size_++;
      return std::pair<iterator, bool>(iterator(this->root_->right), true);
    }

    node_type* parent_node = this->root_->right;
    bool left_direction = key < parent_node->value->first;
    bool good = key != parent_node->value->first;

    while (good && (left_direction ? parent_node->left : parent_node->right)) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = key < parent_node->value->first;
      good = key != parent_node->value->first;
    }

    node_type* result_node = parent_node;

    if (good) {
      node_type* new_node = new node_type(parent_node, key, obj);
      left_direction ? (parent_node->left = new_node)
                     : (parent_node->right = new_node);
      this->size_++;
      result_node = new_node;
    } else
      parent_node->value->second = obj;

    return std::pair<iterator, bool>(iterator(result_node), good);
  }

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

  void merge(map& other) {
    size_type out_i = 0, out_j = 0;
    typedef std::pair<key_type, mapped_type> out_value_type;

    node_type** out_nodes =
        (node_type**)calloc(other.size_, sizeof(node_type*));
    out_value_type** out_values =
        (out_value_type**)calloc(out_j, sizeof(out_value_type*));

    for (iterator i = other.begin(); i != other.end(); ++i) {
      std::pair<iterator, bool> result = this->insert(*i.node->value);

      out_nodes[out_i++] = i.node;

      if (result.second) {
        delete result.first.node->value;
        result.first.node->value = i.node->value;
      } else {
        out_values = (out_value_type**)realloc(
            out_values, sizeof(out_value_type*) * (out_j + 1));
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

  void swap(map& other) {
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
    bool left_direction = key < parent_node->value->first;
    bool result = (key == parent_node->value->first);

    while (!result &&
           (left_direction ? parent_node->left : parent_node->right)) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = key < parent_node->value->first;
      result = key == parent_node->value->first;
    }

    return result;
  }

  mapped_type& at(const key_type& key) {
    if (this->empty()) throw "Out of range";

    node_type* parent_node = this->root_->right;
    bool left_direction = key < parent_node->value->first;
    bool result = (key == parent_node->value->first);

    while (!result &&
           (left_direction ? parent_node->left : parent_node->right)) {
      node_type* temp_node =
          left_direction ? parent_node->left : parent_node->right;
      if (temp_node) parent_node = temp_node;
      left_direction = key < parent_node->value->first;
      result = key == parent_node->value->first;
    }

    if (result)
      return parent_node->value->second;
    else
      throw "Out of range";
  }

  mapped_type& operator[](const key_type& key) {
    try {
      return this->at(key);
    } catch (...) {
      return (*(this->insert(key, mapped_type()).first)).second;
    }
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

  friend std::ostream& operator<<(std::ostream& os,
                                  map<key_type, mapped_type>& m) {
    os << "{";
    for (auto i = m.begin(); i != m.end(); ++i) {
      if (i != m.begin()) os << ", ";
      os << i;
    }
    os << "} (" << m.size() << ")";

    return os;
  }

 private:
  node_type* root_;
  size_type size_;
};
}  // namespace s21

#endif