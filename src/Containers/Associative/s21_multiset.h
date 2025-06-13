#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "s21_rbt.h"

namespace s21 {
template <typename Key>
class multiset : RBT<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using parent = RBT<value_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename parent::iterator;
  using const_iterator = typename parent::const_iterator;
  using size_type = size_t;

 private:
  static key_type get_key(const value_type &v) { return v; };

 public:
  multiset() : parent() {}

  multiset(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      this->_insert(item, get_key, 1);
    }
  }

  iterator begin() { return this->_begin(); }

  iterator end() { return this->_end(); }

  bool empty() const { return this->_empty(); }

  size_type size() const { return this->_size(); }

  size_type max_size() const { return this->_max_size(); }

  void clear() { this->_clear(); }

  iterator insert(const value_type &value) {
    return (this->_insert(value, get_key, 1)).first;
  }

  void erase(iterator pos) { this->_erase(pos); }

  void swap(multiset &other) { this->_swap(other); }

  void merge(multiset &other) { this->_merge(other, get_key, 1); }

  size_type count(const Key &key) {
    return static_cast<size_type>(
        std::distance(lower_bound(key), upper_bound(key)));
  }

  iterator find(const Key &key) { return this->_find(key, get_key); }

  bool contains(const Key &key) { return this->_contains(key, get_key); }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return {lower_bound(key), upper_bound(key)};
  }

  iterator lower_bound(const Key &key) {
    iterator it = this->_begin();
    for (; it != this->_end() && *it < key; ++it) {
    }
    return it;
  }

  iterator upper_bound(const Key &key) {
    iterator it = lower_bound(key);
    for (; it != this->_end() && *it == key; ++it) {
    }
    return it;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return this->_insert_many(get_key, 1, std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif
