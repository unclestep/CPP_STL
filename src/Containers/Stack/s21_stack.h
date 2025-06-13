//
// Created by rasko on 30.03.2025.
//

#ifndef CPP2_S21_CONTAINERS_1_S21_STACK_H
#define CPP2_S21_CONTAINERS_1_S21_STACK_H
#include "../Vector/s21_vector.h"

namespace s21 {
template <class T, class Container = Vector<T>>
class Stack {
 private:
  Container vector;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  Stack &operator=(Stack &&s) noexcept;

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(Stack &other);

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_S21_STACK_H
