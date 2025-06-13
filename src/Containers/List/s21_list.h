#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>

namespace s21 {

template <class T>
class List {
 private:
  struct Node {
    T data;
    Node *next;
    Node *prev;
    Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}
  };

 public:
  class ListIterator {
   private:
    Node *current;

   public:
    ListIterator(Node *node) : current(node) {}

    T &operator*() { return current->data; }

    T *operator->() { return &(current->data); }

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ListIterator &other) const {
      return current != other.current;
    }

    ListIterator &operator++() {
      current = current->next;
      return *this;
    }

    ListIterator &operator--() {
      current = current->prev;
      return *this;
    }
    Node *getNode() const { return current; }
  };

  class ListConstIterator {
   private:
    Node *current;

   public:
    ListConstIterator(Node *node) : current(node) {}

    const T &operator*() const { return current->data; }

    const T *operator->() const { return &(current->data); }

    bool operator==(const ListConstIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ListConstIterator &other) const {
      return current != other.current;
    }

    ListConstIterator &operator++() {
      current = current->next;
      return *this;
    }

    ListConstIterator &operator--() {
      current = current->prev;
      return *this;
    }
    const Node *getNode() const { return current; }
  };

 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  List() : head(nullptr), tail(nullptr) {}
  ~List() { clear(); };
  List(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      if (it == items.begin() && it == NULL) {
        return;
      } else if (it == items.begin() && it != NULL) {
        Node *newNode = new Node(*it);

        head = newNode;
        tail = newNode;
        ;
        continue;
      }
      push_back(*it);
    }
  }
  List(size_type n) {
    head = nullptr;
    tail = nullptr;
    for (size_type i = 0; i < n; i++) {
      push_back(0);
    }
  }
  List(const List &l) : head(nullptr), tail(nullptr) {
    for (auto it = l.cbegin(); it != nullptr; ++it) {
      const Node *tmp = it.getNode();
      push_back(tmp->data);
    }
  }
  List(List &&l) : head(l.head), tail(l.tail) {
    l.head = nullptr;
    l.tail = nullptr;
  }
  List &operator=(List &&l) {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;

    head = l.head;
    tail = l.tail;

    l.head = nullptr;
    l.tail = nullptr;
    return *this;
  }

  iterator begin() { return iterator(head); }

  iterator end() { return iterator(tail); }

  const_iterator cbegin() const { return const_iterator(head); }

  const_iterator cend() const { return const_iterator(tail); }
  void push_back(const_reference value) {
    Node *newNode = new Node(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      return;
    }
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    return;
  }
  void push_front(const_reference value) {
    Node *newNode = new Node(value);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
    return;
  }
  void pop_back() {
    if (head == nullptr) {
      return;  // empty list
    }

    if (head == tail) {  // only one node
      delete head;
      head = tail = nullptr;
      return;
    }

    Node *tmp = tail->prev;
    tail->prev->next = nullptr;
    delete tail;
    tail = tmp;
  }
  void pop_front() {
    if (head == nullptr) {
      return;  // empty list
    }

    if (head == tail) {  // only one node
      delete head;
      head = tail = nullptr;
      return;
    }
    Node *tmp = head->next;
    delete head;
    head = tmp;
  }
  bool empty() { return head == nullptr; }
  size_type size() {
    if (empty()) {
      return 0;
    }
    int counter = 0;
    for (auto it = begin(); it != nullptr; ++it) {
      counter++;
    }
    return counter;
  }
  size_type max_size() {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }
  iterator insert(iterator pos, const_reference value) {
    Node *curr = pos.getNode();
    if (pos == nullptr) {
      return nullptr;
    }
    if (pos == begin()) {
      push_front(value);
      --pos;
      return pos;
    }

    Node *newNode = new Node(value);

    curr->prev->next = newNode;
    curr->prev = newNode;
    newNode->next = curr;
    --pos;
    return pos;
  }
  void clear() {
    Node *curr = head;
    while (curr != nullptr) {
      Node *next = curr->next;
      delete curr;
      curr = next;
    }
    head = nullptr;
    tail = nullptr;
  }
  void erase(iterator pos) {
    Node *curr = pos.getNode();

    if (pos == begin()) {
      pop_front();
    } else if (pos == end()) {
      pop_back();
    } else if (pos == nullptr) {
      return;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    curr->next = nullptr;
    curr->prev = nullptr;
    delete curr;
  }
  const_reference front() { return *(begin()); }
  const_reference back() { return *(end()); }
  void swap(List &other) {
    if (other.head == this->head) {
      return;
    }

    Node *tmph = other.head;
    Node *tmpt = other.tail;

    other.head = head;
    other.tail = tail;

    head = tmph;
    tail = tmpt;
  }
  void sort() {
    if (head == nullptr) return;

    bool swapped;
    Node *curr;
    Node *last = nullptr;

    do {
      swapped = false;
      curr = head;
      while (curr->next != last) {
        if (curr->data > curr->next->data) {
          int swap_data = curr->data;
          curr->data = curr->next->data;
          curr->next->data = swap_data;

          swapped = true;
        }
        curr = curr->next;
      }
      last = curr;
    } while (swapped);
  }
  void merge(List &other) {
    if (head == nullptr && other.head == nullptr) return;
    tail->next = other.head;
    other.tail->prev = tail;
    tail = other.tail;
    other.tail = nullptr;
    other.head = nullptr;
    sort();
  }
  void reverse() {
    Node *curr = head;
    while (curr != nullptr) {
      Node *tmp = curr->next;

      curr->next = curr->prev;
      curr->prev = tmp;

      curr = curr->prev;
    }
    Node *tmp = head;

    head = tail;
    tail = tmp;
  }
  void unique() {
    if (head == nullptr) {
      return;
    }
    Node *curr = head;
    while (curr != nullptr && curr->next != nullptr) {
      Node *tmp = curr->next;
      if (curr->data == tmp->data) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        curr = tmp;
        continue;
      } else {
        curr = curr->next;
      }
    }
  }
  void splice(const_iterator pos, List &other) {
    if (other.empty()) return;

    const Node *pos_node = pos.getNode();

    if (pos_node == head) {
      other.tail->next = head;
      if (head) head->prev = other.tail;
      head = other.head;
    } else if (pos_node == tail) {
      tail->next = other.head;
      other.head->prev = tail;
      tail = other.tail;
    } else {
      Node *curr = const_cast<Node *>(pos_node);
      Node *prev_node = curr->prev;

      prev_node->next = other.head;
      other.head->prev = prev_node;
      other.tail->next = curr;
      curr->prev = other.tail;
    }

    other.head = other.tail = nullptr;
  }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (push_front(std::forward<Args>(args)), ...);
  }
  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    (insert(pos, std::forward<Args>(args)), ...);
    return pos;
  }

 private:
  Node *head;
  Node *tail;
};

}  // namespace s21

#endif  // S21_LIST