#include <cstddef>
#ifndef S21_ARRAY_H
#define S21_ARRAY_H

namespace s21 {

template <class T, std::size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  T arr[N];
  int size_a = N;

 public:
  Array() : size_a(N) {}
  Array(std::initializer_list<value_type> const &items) {
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
  };
  ~Array() { size_a = 0; }
  Array(const Array &a) {
    iterator it1 = begin();
    const_iterator it = a.cbegin();
    for (; it < a.cend() + 1; it++, it1++) {
      *it1 = *it;
    }
    size_a = a.size();
  }
  Array(Array &&a) : size_a(a.size_a) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = std::move(a.arr[i]);
    }
  }

  reference operator[](size_type pos) { return arr[pos]; }

  iterator begin() { return arr; }

  iterator end() { return arr + N - 1; }
  const_iterator cbegin() const { return arr; }

  const_iterator cend() const { return arr + N - 1; }

  bool empty() { return N == 0; }
  size_type size() const { return size_a; }
  size_type max_size() { return size_a; }
  Array &operator=(Array &&a) noexcept {
    if (this != &a) {
      for (size_t i = 0; i < N; ++i) {
        arr[i] = std::move(a.arr[i]);
      }
    }
    return *this;
  }
  iterator data() { return arr; }
  const_reference back() { return *(end()); }
  const_reference front() { return *(begin()); }
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Index out of range");
    }
    return arr[pos];
  }
  void swap(Array &other) {
    value_type tmparr[N];
    int tmps = size_a;
    for (int i = 0; i < other.size_a; ++i) {
      tmparr[i] = arr[i];
    }
    size_a = other.size_a;
    for (int i = 0; i < other.size_a; ++i) {
      arr[i] = other.arr[i];
    }

    other.size_a = tmps;
    for (int i = 0; i < other.size_a; ++i) {
      other.arr[i] = tmparr[i];
    }
  }
  void fill(const_reference value) {
    for (int i = 0; i < size_a; i++) {
      arr[i] = value;
    }
  }
};
}  // namespace s21

#endif
