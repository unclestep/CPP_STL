#ifndef S21_RBT_H
#define S21_RBT_H

#include <iterator>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "../Vector/s21_vector.h"
/* ####################### */
/* # RED-BLACK TREE NODE # */
/* ####################### */
enum class Color : bool { RED, BLACK };

template <typename Value>
struct RBTNode {
  Value value;
  Color color;
  RBTNode *left;
  RBTNode *right;
  RBTNode *parent;

  RBTNode()
      : value{},
        color(Color::BLACK),
        left(nullptr),
        right(nullptr),
        parent(nullptr) {}

  RBTNode(const Value &v, Color c)
      : value(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}

  RBTNode(const Value &v, Color c, RBTNode *l, RBTNode *r, RBTNode *p)
      : value(v), color(c), left(l), right(r), parent(p) {}
};
/* ############################## */
/* # END OF RED-BLACK TREE NODE # */
/* ############################## */

/* ########################### */
/* # RED-BLACK TREE ITERATOR # */
/* ########################### */
template <typename Value>
class RBTIterator {
 public:
  using value_type = Value;
  using reference = value_type &;
  using pointer = value_type *;
  using node_type = RBTNode<value_type>;
  using difference_type = std::ptrdiff_t;

 private:
  node_type *node;
  node_type *nil;
  node_type *root;

 public:
  RBTIterator() : node(nullptr), nil(nullptr), root(nullptr) {}
  RBTIterator(node_type *node, node_type *nil, node_type *root)
      : node(node), nil(nil), root(root) {}

  RBTIterator(const RBTIterator &other)
      : node(other.node), nil(other.nil), root(other.root) {}

  ~RBTIterator() {
    node = nullptr;
    nil = nullptr;
    root = nullptr;
  }

  RBTIterator &operator=(const RBTIterator &other) {
    RBTIterator tmp(other);
    swap(tmp);
    return *this;
  }

  RBTIterator &operator=(RBTIterator &&other) noexcept {
    swap(other);
    return *this;
  }

  bool operator==(const RBTIterator &other) const { return node == other.node; }

  bool operator!=(const RBTIterator &other) const { return node != other.node; }

  reference operator*() const { return node->value; }

  pointer operator->() const { return &(node->value); }

  RBTIterator &operator++() {
    if (node->right == nil) {
      while (node->parent != nil && node == node->parent->right) {
        node = node->parent;
      }
      node = node->parent;
    } else {
      node = node->right;
      while (node->left != nil) {
        node = node->left;
      }
    }
    return *this;
  }

  RBTIterator operator++(int) {
    RBTIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  RBTIterator &operator--() {
    if (node == nil) {
      node = root;
      while (node->right != nil) {
        node = node->right;
      }
    } else if (node->left == nil) {
      while (node->parent != nil && node == node->parent->left) {
        node = node->parent;
      }
      node = node->parent;
    } else if (node->left != nil) {
      node = node->left;
      while (node->right != nil) {
        node = node->right;
      }
    }
    return *this;
  }

  RBTIterator operator--(int) {
    RBTIterator tmp(*this);
    --(*this);
    return tmp;
  }

  void swap(RBTIterator &other) noexcept {
    std::swap(node, other.node);
    std::swap(nil, other.nil);
    std::swap(root, other.root);
  }

  node_type *getNode() const { return node; }

  node_type *getNil() const { return nil; }

  node_type *getRoot() const { return root; }
};
/* ################################## */
/* # END OF RED-BLACK TREE ITERATOR # */
/* ################################## */

/* ################################# */
/* # RED-BLACK TREE CONST ITERATOR # */
/* ################################# */
template <typename Value>
class RBTConstIterator {
 public:
  using value_type = Value;
  using const_reference = const value_type &;
  using const_pointer = const value_type *;
  using node_type = RBTNode<value_type>;
  using difference_type = std::ptrdiff_t;

 private:
  node_type *node;
  node_type *nil;
  node_type *root;

 public:
  RBTConstIterator() : node(nullptr), nil(nullptr), root(nullptr) {}

  RBTConstIterator(node_type *node, node_type *nil, node_type *root)
      : node(node), nil(nil), root(root) {}

  RBTConstIterator(const RBTConstIterator &other)
      : node(other.node), nil(other.nil), root(other.root) {}

  ~RBTConstIterator() {
    node = nullptr;
    nil = nullptr;
    root = nullptr;
  }

  RBTConstIterator &operator=(const RBTConstIterator &other) {
    RBTConstIterator tmp(other);
    swap(tmp);
    return *this;
  }

  RBTConstIterator &operator=(RBTConstIterator &&other) noexcept {
    swap(other);
    return *this;
  }

  bool operator==(const RBTConstIterator &other) const {
    return node == other.node;
  }

  bool operator!=(const RBTConstIterator &other) const {
    return node != other.node;
  }

  const_reference operator*() const { return node->value; }

  const_pointer operator->() const { return &(node->value); }

  RBTConstIterator &operator++() {
    if (node->right == nil) {
      while (node->parent != nil && node == node->parent->right) {
        node = node->parent;
      }
      node = node->parent;
    } else {
      node = node->right;
      while (node->left != nil) {
        node = node->left;
      }
    }
    return *this;
  }

  RBTConstIterator operator++(int) {
    RBTConstIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  RBTConstIterator &operator--() {
    if (node == nil) {
      node = root;
      while (node->right != nil) {
        node = node->right;
      }
    } else if (node->left == nil) {
      while (node->parent != nil && node == node->parent->left) {
        node = node->parent;
      }
      node = node->parent;
    } else if (node->left != nil) {
      node = node->left;
      while (node->right != nil) {
        node = node->right;
      }
    }
    return *this;
  }

  RBTConstIterator operator--(int) {
    RBTConstIterator tmp(*this);
    --(*this);
    return tmp;
  }

  void swap(RBTConstIterator &other) noexcept {
    std::swap(node, other.node);
    std::swap(nil, other.nil);
    std::swap(root, other.root);
  }

  node_type *getNode() const { return node; }

  node_type *getNil() const { return nil; }

  node_type *getRoot() const { return root; }
};
/* ######################################## */
/* # END OF RED-BLACK TREE CONST ITERATOR # */
/* ######################################## */

/* ################################# */
/* # RED-BLACK TREE DATA STRUCTURE # */
/* ################################# */
template <typename Value>
class RBT {
 public:
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = RBTIterator<value_type>;
  using const_iterator = RBTConstIterator<value_type>;
  using size_type = size_t;
  using node_type = RBTNode<value_type>;

 private:
  node_type *root;
  node_type *nil;
  size_type size;

  node_type *min(node_type *start_node) const {
    node_type *cur = start_node;
    while (cur && cur->left != nil) {
      cur = cur->left;
    }
    return cur;
  }

  void clearTree(node_type *node) {
    if (node != nil && nil && node) {
      clearTree(node->left);
      clearTree(node->right);
      delete node;
    }
  }

  node_type *deepCopy(node_type *otherNode, node_type *otherNil) {
    node_type *newNode = nil;

    if (otherNode && otherNode != otherNil) {
      newNode = new node_type(otherNode->value, otherNode->color);

      newNode->left = deepCopy(otherNode->left, otherNil);
      if (newNode->left != nil) newNode->left->parent = newNode;

      newNode->right = deepCopy(otherNode->right, otherNil);
      if (newNode->right != nil) newNode->right->parent = newNode;

      newNode->parent = nil;
    }

    return newNode;
  }

  void fixInsert(node_type *y) {
    node_type *p = y->parent;
    node_type *g = p->parent;
    bool isLeft = g->left == p;
    node_type *u = isLeft ? g->right : g->left;

    if (y == root) {
      y->color = Color::BLACK;
    } else if (y->parent->color == Color::BLACK) {
      y->color = Color::RED;
    } else if (u->color == Color::RED) {
      p->color = Color::BLACK;
      u->color = Color::BLACK;
      g->color = Color::RED;
      fixInsert(g);
    } else if (u->color == Color::BLACK) {
      rotate(y, p, g, u);
    }
  }

  void rightRotate(node_type *y) {
    node_type *x = y->left;
    y->left = x->right;

    if (x->right != nil) x->right->parent = y;

    x->right = y;
    x->parent = y->parent;

    if (y->parent == nil) {
      root = x;
    } else if (y == y->parent->left) {
      y->parent->left = x;
    } else if (y == y->parent->right) {
      y->parent->right = x;
    }

    y->parent = x;
  }

  void leftRotate(node_type *y) {
    node_type *x = y->right;
    y->right = x->left;

    if (x->left != nil) x->left->parent = y;

    x->left = y;
    x->parent = y->parent;

    if (y->parent == nil) {
      root = x;
    } else if (y == y->parent->left) {
      y->parent->left = x;
    } else if (y == y->parent->right) {
      y->parent->right = x;
    }

    y->parent = x;
  }

  void LLRotation(node_type *p, node_type *g) {
    rightRotate(g);
    std::swap(g->color, p->color);
  }

  void LRRotation(node_type *y, node_type *p, node_type *g) {
    leftRotate(p);
    LLRotation(p, g);
    std::swap(g->color, y->color);
  }

  void RRRotation(node_type *p, node_type *g) {
    leftRotate(g);
    std::swap(g->color, p->color);
  }

  void RLRotation(node_type *y, node_type *p, node_type *g) {
    rightRotate(p);
    RRRotation(p, g);
    std::swap(g->color, y->color);
  }

  void rotate(node_type *y, node_type *p, node_type *g, node_type *u) {
    if (p == u && y == p->left) {
      LLRotation(p, g);
    } else if (p == u && y == p->right) {
      LRRotation(y, p, g);
    } else if (p == u && y == p->right) {
      RRRotation(p, g);
    } else if (p == u && y == p->left) {
      RLRotation(y, p, g);
    }
  }

  node_type *fixDeleteIfXIsLeft(node_type *x) {
    node_type *s = x->parent->right;
    if (s->color == Color::RED) {
      s->color = Color::BLACK;
      x->parent->color = Color::RED;
      leftRotate(x->parent);
      s = x->parent->right;
    }
    if (s->left->color == Color::BLACK && s->right->color == Color::BLACK) {
      s->color = Color::RED;
      x = x->parent;
    } else {
      if (s->right->color == Color::BLACK) {
        s->left->color = Color::BLACK;
        s->color = Color::RED;
        rightRotate(s);
        s = x->parent->right;
      }
      s->color = x->parent->color;
      x->parent->color = Color::BLACK;
      s->right->color = Color::BLACK;
      leftRotate(x->parent);
      x = root;
    }
    return x;
  }

  node_type *fixDeleteIfXIsRight(node_type *x) {
    node_type *s = x->parent->left;
    if (s->color == Color::RED) {
      s->color = Color::BLACK;
      x->parent->color = Color::RED;
      rightRotate(x->parent);
      s = x->parent->left;
    }
    if (s->left->color == Color::BLACK && s->right->color == Color::BLACK) {
      s->color = Color::RED;
      x = x->parent;
    } else {
      if (s->left->color == Color::BLACK) {
        s->right->color = Color::BLACK;
        s->color = Color::RED;
        leftRotate(s);
        s = x->parent->left;
      }
      s->color = x->parent->color;
      x->parent->color = Color::BLACK;
      s->left->color = Color::BLACK;
      rightRotate(x->parent);
      x = root;
    }
    return x;
  }

  void fixDelete(node_type *x) {
    while (x != root && x->color == Color::BLACK) {
      if (x == x->parent->left) {
        x = fixDeleteIfXIsLeft(x);
      } else {
        x = fixDeleteIfXIsRight(x);
      }
    }
    x->color = Color::BLACK;
  }

  void transplant(node_type *u, node_type *v) {
    if (u->parent == nil) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else if (u == u->parent->right) {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  node_type *detachNode(iterator pos) {
    node_type *z = pos.getNode();
    node_type *y = z;
    Color y_initial_color = y->color;
    node_type *x = nullptr;

    if (z->left == nil) {
      x = z->right;
      transplant(z, x);
    } else if (z->right == nil) {
      x = z->left;
      transplant(z, x);
    } else if (z->left != nil && z->right != nil) {
      y = min(z->right);
      y_initial_color = y->color;
      x = y->right;

      if (y->parent != z) { /* if y is indirect successor */
        transplant(y, x);
        y->right = z->right;
        y->right->parent = y;
      }

      transplant(z, y);
      y->left = z->left;
      z->left->parent = y;
      y->color = z->color;
    }

    z->parent = z->left = z->right = nullptr;
    --size;

    if (y_initial_color == Color::BLACK) fixDelete(x);

    return z;
  }

  template <typename Getter>
  void attachNode(node_type *attachNode, Getter get_key, bool duplicates) {
    node_type *parent = nil;
    node_type *cur = root;
    auto key = get_key(attachNode->value);
    bool isLeft = 0;

    while (cur != nil) {
      parent = cur;
      if (key < get_key(cur->value)) {
        cur = cur->left;
        isLeft = 1;
      } else if (key > get_key(cur->value) || duplicates) {
        cur = cur->right;
        isLeft = 0;
      }
    }

    attachNode->left = attachNode->right = attachNode->parent = nil;
    if (parent == nil) {
      root = attachNode;
    } else if (isLeft) {
      attachNode->parent = parent;
      parent->left = attachNode;
    } else if (!isLeft) {
      attachNode->parent = parent;
      parent->right = attachNode;
    }

    ++size;
    fixInsert(attachNode);
  }

 protected:
  /* RULE OF FIVE */
  RBT() : root(nullptr), nil(nullptr), size(0) {
    nil = new node_type();
    nil->left = nil->right = nil->parent = nil;
    root = nil;
  }

  RBT(const RBT &other) : RBT() {
    size = other.size;
    root = deepCopy(other.root, other.nil);
  }

  RBT(RBT &&other) noexcept
      : root(other.root), nil(other.nil), size(other.size) {
    other.root = nullptr;
    other.nil = nullptr;
    other.size = 0U;
  }

  ~RBT() {
    clearTree(root);
    size = 0;
    delete nil;
  }

  RBT &operator=(const RBT &other) {
    RBT tmp(other);
    _swap(tmp);
    return *this;
  }

  RBT &operator=(RBT &&other) {
    _swap(other);
    return *this;
  }
  /* END OF RULE OF FIVE*/

  /* ITERATORS */
  iterator _begin() { return iterator(min(root), nil, root); }

  const_iterator _begin() const { return const_iterator(min(root), nil, root); }

  iterator _end() { return iterator(nil, nil, root); }

  const_iterator _end() const { return const_iterator(nil, nil, root); }
  /* END OF ITERATORS */

  /* CAPACITY */
  bool _empty() const { return size == 0; }

  size_type _size() const { return size; }

  size_type _max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }
  /* END OF CAPACITY */

  /* MODIFIERS */
  void _clear() {
    clearTree(root);
    root = nil;
    size = 0U;
  }

  template <typename Getter>
  std::pair<iterator, bool> _insert(const value_type &value, Getter get_key,
                                    bool duplicates) {
    node_type *parent = nil;
    node_type *cur = root;
    auto key = get_key(value);
    bool isLeft = 0;
    iterator it;
    bool success = 1;

    while (cur != nil && success) {
      parent = cur;
      if (key < get_key(cur->value)) {
        cur = cur->left;
        isLeft = 1;
      } else if (key > get_key(cur->value) || duplicates) {
        cur = cur->right;
        isLeft = 0;
      } else {
        it = iterator(cur, nil, root);
        success = 0;
      }
    }

    if (success) {
      node_type *newNode = new node_type(value, Color::RED, nil, nil, parent);

      if (parent == nil) {
        root = newNode;
      } else if (isLeft) {
        parent->left = newNode;
      } else if (!isLeft) {
        parent->right = newNode;
      }

      ++size;
      fixInsert(newNode);
      it = iterator(newNode, nil, root);
    }

    return {it, success};
  }

  void _erase(iterator pos) {
    node_type *z = nullptr;
    node_type *y = nullptr;
    Color y_initial_color = Color::RED;
    if (pos != _end() && pos.getNode() != nil && pos.getNode() != nullptr) {
      z = pos.getNode();
      y = z;
      y_initial_color = y->color;
    }
    node_type *x = nullptr;

    if (z && z->left == nil) {
      x = z->right;
      transplant(z, x);
    } else if (z && z->right == nil) {
      x = z->left;
      transplant(z, x);
    } else if (z && z->left != nil && z->right != nil) {
      y = min(z->right);
      y_initial_color = y->color;
      x = y->right;

      if (y->parent != z) { /* if y is indirect successor */
        transplant(y, x);
        y->right = z->right;
        y->right->parent = y;
      }

      transplant(z, y);
      y->left = z->left;
      z->left->parent = y;
      y->color = z->color;
    }

    if (z) {
      delete z;
      --size;
    }

    if (y_initial_color == Color::BLACK) fixDelete(x);
  }

  void _swap(RBT &other) noexcept {
    std::swap(root, other.root);
    std::swap(nil, other.nil);
    std::swap(size, other.size);
  }

  template <typename Getter>
  void _merge(RBT &other, Getter get_key, bool duplicates) {
    std::vector<iterator> moving;
    for (auto it = other._begin(); it != other._end(); ++it) {
      if (!_contains(get_key(*it), get_key) || duplicates) {
        moving.push_back(it);
      }
    }
    for (auto it : moving) {
      node_type *n = other.detachNode(it);
      attachNode(n, get_key, duplicates);
    }
  }
  /* END OF MODIFIERS */

  /* LOOKUP */
  template <typename Key, typename Getter>
  iterator _find(const Key &key, Getter get_key) {
    node_type *cur = root;
    iterator res = _end();

    while (cur != nil && res == _end()) {
      if (key < get_key(cur->value)) {
        cur = cur->left;
      } else if (key > get_key(cur->value)) {
        cur = cur->right;
      } else {
        res = iterator(cur, nil, root);
      }
    }

    return res;
  }

  template <typename Key, typename Getter>
  bool _contains(const Key &key, Getter get_key) {
    return _find(key, get_key) != _end();
  }
  /* END OF LOOKUP */

  /* EXTRA */
  template <typename Getter, typename... Args>
  std::vector<std::pair<iterator, bool>> _insert_many(Getter get_key,
                                                      bool duplicates,
                                                      Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    if constexpr (sizeof...(Args) > 0) {
      (result.push_back(_insert(std::forward<Args>(args), get_key, duplicates)),
       ...);
    }
    return result;
  }
  /* END OF EXTRA */

 public:
  /* GETTERS */
  node_type *getRoot() const { return root; }

  node_type *getNil() const { return nil; }
  /* END OF GETTERS */
};
/* ######################################## */
/* # END OF RED-BLACK TREE DATA STRUCTURE # */
/* ######################################## */

#endif