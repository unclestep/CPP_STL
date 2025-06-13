#ifndef S21_SET_H
#define S21_SET_H

#include "s21_rbt.h"

namespace s21 {
template <typename Key>
class set : RBT<Key> {
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
  set() : parent() {}

  set(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      this->_insert(item, get_key, 0);
    }
  }

  iterator begin() { return this->_begin(); }

  iterator end() { return this->_end(); }

  bool empty() { return this->_empty(); }

  size_type size() { return this->_size(); }

  size_type max_size() { return this->_max_size(); }

  void clear() { this->_clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return this->_insert(value, get_key, 0);
  }

  void erase(iterator pos) { this->_erase(pos); }

  void swap(set &other) { this->_swap(other); }

  void merge(set &other) { this->_merge(other, get_key, 0); }

  iterator find(const Key &key) { return this->_find(key, get_key); }

  bool contains(const Key &key) { return this->_contains(key, get_key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return this->_insert_many(get_key, 0, std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif
