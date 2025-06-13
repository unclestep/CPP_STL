#ifndef CPP2_S21_CONTAINERS_1_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_1_S21_QUEUE_H

#include "../List/s21_list.h"

namespace s21 {
template <class T, class Container = List<T>>
class Queue {
 private:
  Container list;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue() : list() {}
  Queue(std::initializer_list<value_type> const &items) : list(items) {}

  const_reference front() { return list.front(); }
  const_reference back() { return list.back(); }

  void push(const_reference value) { list.push_back(value); }
  void pop() { list.pop_front(); }
  bool empty() { return list.empty(); }
  ~Queue() { list.clear(); }
  Queue(const Queue &q) : list(q.list) {}
  Queue(Queue &&q) : list(std::move(q.list)) {}
  Queue &operator=(Queue &&q) {
    list = std::move(q.list);
    return *this;
  }
  size_type size() { return list.size(); }
  void swap(Queue &other) { list.swap(other.list); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }
};
}  // namespace s21
#endif
