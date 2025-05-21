#ifndef S21_RBT_H
#define S21_RBT_H

#include <utility>
#include <iterator>
#include <limits>

/* ################### */
/* RED-BLACK TREE NODE */
/* ################### */
enum class Color : bool {
    RED,
    BLACK
};

template <typename Value>
struct RBTNode {
    Value value;
    Color color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;

    RBTNode() : value{}, color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}

    RBTNode(const Value& v, Color c) : 
        value(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}

    RBTNode(const Value& v, Color c, RBTNode* l, RBTNode* r, RBTNode* p) :
        value(v), color(c), left(l), right(r), parent(p) {}
};
/* ########################## */
/* END OF RED-BLACK TREE NODE */
/* ########################## */



/* ####################### */
/* RED-BLACK TREE ITERATOR */
/* ####################### */
template <typename Value>
class RBTIterator {
private:
    RBTNode<Value>* node;
    RBTNode<Value>* nil;
    RBTNode<Value>* root;
public:
    using value_type = Value;
    using reference = value_type&;
    using pointer = value_type*;

    RBTIterator() 
        : node(nullptr), nil(nullptr), root(nullptr) {}
    RBTIterator(RBTNode<Value>* node, RBTNode<Value>* nil, RBTNode<Value>* root) 
        : node(node), nil(nil), root(root) {}

    RBTIterator(const RBTIterator<Value>& other) 
        : node(other.node), nil(other.nil), root(other.root) {}    

    bool operator == (const RBTIterator<Value>& other) const {
        return node == other.node;
    }

    bool operator != (const RBTIterator<Value>& other) const {
        return node != other.node;
    } 

    reference operator * () const {
        return node->value;
    }

    pointer operator -> () const {
        return &(node->value);
    }

    RBTIterator& operator++ () {
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

    RBTIterator operator++ (int) {
        RBTIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    RBTIterator& operator-- () {
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

    RBTIterator operator-- (int) {
        RBTIterator tmp(*this);
        --(*this);
        return tmp;
    }

};
/* ############################## */
/* END OF RED-BLACK TREE ITERATOR */
/* ############################## */



/* ############################# */
/* RED-BLACK TREE CONST ITERATOR */
/* ############################# */
template <typename Value>
class RBTConstIterator {
private:
    RBTNode<Value>* node;
    RBTNode<Value>* nil;
    RBTNode<Value>* root;
public:
    using value_type = Value;
    using const_reference = const value_type&;
    using const_pointer = const value_type*;

    RBTConstIterator() 
        : node(nullptr), nil(nullptr), root(nullptr) {}

    RBTConstIterator(RBTNode<Value>* node, RBTNode<Value>* nil, RBTNode<Value>* root) 
        : node(node), nil(nil), root(root) {}
        
    RBTConstIterator(const RBTConstIterator<Value>& other) 
        : node(other.node), nil(other.nil), root(other.root) {} 

    bool operator == (const RBTConstIterator<Value>& other) const {
        return node == other.node;
    }

    bool operator != (const RBTConstIterator<Value>& other) const {
        return node != other.node;
    } 

    const_reference operator * () const {
        return node->value;
    }

    const_pointer operator -> () const {
        return &(node->value);
    }

    RBTConstIterator& operator++ () {
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

    RBTConstIterator operator++ (int) {
        RBTConstIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    RBTConstIterator& operator-- () {
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

    RBTConstIterator operator-- (int) {
        RBTConstIterator tmp(*this);
        --(*this);
        return tmp;
    }
};
/* ######################################## */
/* # END OF RED-BLACK TREE CONST ITERATOR # */
/* ######################################## */



/* ################################# */
/* # RED-BLACK TREE DATA STRUCTURE # */
/* ################################# */
template <typename Key, typename Value>
class RBT {
public:
    using key_type = Key;
    using value_type = Value;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = RBTIterator<Value>;
    using const_iterator = RBTConstIterator<Value>;
    using size_type = size_t;
    using node_type = RBTNode<value_type>;
private:
    node_type* root;
    node_type* nil;
    size_type size;

    node_type* min() const {
        node_type* cur = root;
        while (cur->left != nil) {
            cur = cur->left;
        }
        return cur;
    }

    void clearTree(node_type* node) {
        if (node && node != nil) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

    node_type* deepCopy(node_type* otherNode, node_type* otherNil) {
        node_type* newNode = nil;

        if (otherNode && otherNode != otherNil) {
            newNode = new node_type(otherNode->value, otherNode->color);

            newNode->left = deepCopy(otherNode->left, otherNil);
            if (newNode->left != nil)
                newNode->left->parent = newNode;

            newNode->right = deepCopy(otherNode->right, otherNil);
            if (newNode->right != nil)
                newNode->right->parent = newNode;

            newNode->parent = nil;
        }

        return newNode;
    }

    void fix(node_type* y) {
        node_type* p = y->parent;
        node_type* g = p->parent;
        bool isLeft = g->left == p;
        node_type* u = isLeft ? g->right : g->left;

        if (y == root) {
            y->color = Color::BLACK;
        } else if (y->parent->color == Color::BLACK) {
            y->color = Color::RED;
        } else if (u->color == Color::RED) {
            p->color = Color::BLACK;
            u->color = Color::BLACK;
            g->color = Color::RED;
            fix(g);
        } else if (u->color == Color::BLACK) {
            rotate(y, p, g, u);
        }
    }

    void rightRotate(node_type* y) {
        node_type* x = y->left;
        y->left = x->right;

        if (x->right != nil)
            x->right->parent = y;

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

    void leftRotate(node_type* y) {
        node_type* x = y->right;
        y->right = x->left;

        if (x->left != nil)
            x->left->parent = y;

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

    void LLRotation(node_type* y, node_type* p, node_type* g, node_type* u) {
        rightRotate(g);
        std::swap(g->color, p->color);
    }

    void LRRotation(node_type* y, node_type* p, node_type* g, node_type* u) {
        leftRotate(p);
        LLRotation(y, p, g, u);
        std::swap(g->color, y->color);
    }

    void RRRotation(node_type* y, node_type* p, node_type* g, node_type* u) {
        leftRotate(g);
        std::swap(g->color, p->color);
    }

    void RLRotation(node_type* y, node_type* p, node_type* g, node_type* u) {
        rightRotate(p);
        RRRotation(y, p, g, u);
        std::swap(g->color, y->color);
    }

    void rotate(node_type* y, node_type* p, node_type* g, node_type* u) {
        if (p == g->left && y == p->left) {
            LLRotation(y, p, g, u);
        } else if (p == g->left && y == p->right) {
            LRRotation(y, p, g, u);
        } else if (p == g->right && y == p->right) {
            RRRotation(y, p, g, u);
        } else if (p == g->right && y == p->left) {
            RLRotation(y, p, g, u);
        }
    }

protected:
    RBT() : root(nullptr), nil(nullptr), size(0) {
        nil = new node_type();
        nil->left = nil->right = nil->parent = nil;
        root = nil;
    }

    RBT(const RBT& other) : RBT() {
        size = other.size;
        root = deepCopy(other.root, other.nil);
    }

    RBT(RBT&& other) noexcept
        : root(other.root), nil(other.nil), size(other.size) {
        other.root = nullptr;
        other.nil = nullptr;
        other.size = 0;
    }

    ~RBT() {
        clearTree(root);
        size = 0;
        delete nil;
    }

    RBT& operator = (const RBT& other) {
        RBT<Key, Value> tmp(other);
        swap(tmp);
        return *this;
    }

    RBT& operator = (RBT&& other) {
        swap(other);
        return *this;
    }

    /* ITERATORS */
    iterator _begin() {
        return iterator(min(), nil, root);
    }

    const_iterator _begin() const {
        return const_iterator(min(), nil, root);
    }

    iterator _end() {
        return iterator(nil, nil, root);
    }

    const_iterator _end() const {
        return const_iterator(nil, nil, root);
    }
    /* END OF ITERATORS */

    /* CAPACITY */
    bool _empty() const {
        return size == 0;
    }

    size_type _size() const {
        return size;
    }

    size_type _max_size() const {
        return std::numeric_limits<size_type>::max();
    }
    /* END OF CAPACITY */

    /* MODIFIERS */
    void _clear() {
        clearTree(root);
        root = nil;
        size = 0;
    }

    void _swap(RBT& other) noexcept {
        std::swap(root, other.root);
        std::swap(nil, other.nil);
        std::swap(size, other.size);
    }

    template <typename Getter>
    std::pair<iterator, bool> _insert(const value_type& value, Getter get_key) {
        node_type* parent = nil;
        node_type* cur = root;
        key_type key = get_key(value);
        bool isLeft = false;
        std::pair<iterator, bool> res = {iterator(cur, nil, root), true};

        while (cur != nil && res.second) {
            parent = cur;
            if (key < get_key(cur->value)) {
                cur = cur->left;
                isLeft = true;
            } else if (key > get_key(cur->value)) {
                cur = cur->right;
                isLeft = false;
            } else {
                res = {iterator(cur, nil, root), false};
            }
        }

        if (res.second) {
            node_type* newNode = new node_type(value, Color::RED, nil, nil, parent);

            if (parent == nil) {
                root = newNode;
            } else if (isLeft) {
                parent->left = newNode;
            } else if (!isLeft) {
                parent->right = newNode;
            }

            ++size;
            fix(newNode);
            res = {iterator(newNode, nil, root), true};
        }

        return res;
    }
    
    template <typename Key, typename Getter>
    iterator _find(const Key& key, Getter get_key) {
        node_type* cur = root;
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
    bool _contains(const Key& key, Getter get_key) {
        return _find(key, get_key) != _end();
    }

    void _erase(iterator pos) {

    }
};

#endif