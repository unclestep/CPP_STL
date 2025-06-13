#ifndef S21_MAP_H
#define S21_MAP_H

#include "s21_rbt.h"

namespace s21 {
template <typename Key, typename T>
class map : RBT<std::pair<const Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using parent = RBT<value_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename parent::iterator;
  using const_iterator = typename parent::const_iterator;
  using size_type = size_t;

 private:
  static key_type get_key(const value_type &v) { return v.first; };

 public:
  map() : parent() {}

  map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      this->_insert(item, get_key, 0);
    }
  }

  T &at(const Key &key) {
    auto it = this->_find(key, get_key);
    if (it == this->_end()) {
      throw std::out_of_range("Key was not found!");
    } else {
      return it->second;
    }
  }

  T &operator[](const Key &key) {
    T *res = nullptr;
    auto it = this->_find(key, get_key);

    if (it == this->_end()) {
      auto r = this->_insert(std::make_pair(key, T{}), get_key, 0);
      res = &(r.first->second);
    } else {
      res = &(it->second);
    }

    return *res;
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

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return this->_insert(std::make_pair(key, obj), get_key, 0);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto it = this->_find(key, get_key);
    bool success = 0;

    if (it == this->_end()) {
      auto r = this->_insert(std::make_pair(key, obj), get_key, 0);
      it = r.first;
      success = r.second;
    } else {
      it->second = obj;
    }

    return {it, success};
  }

  void erase(iterator pos) { this->_erase(pos); }

  void swap(map &other) { this->_swap(other); }

  void merge(map &other) { this->_merge(other, get_key, 0); }

  iterator find(const Key &key) { return this->_find(key, get_key); }

  bool contains(const Key &key) { return this->_contains(key, get_key); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return this->_insert_many(get_key, 0, std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif