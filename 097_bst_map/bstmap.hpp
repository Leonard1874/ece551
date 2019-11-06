#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    Node * left;
    Node * right;
    K key;
    V value;
    Node() : left(NULL), right(NULL), key(NULL), value(NULL) {}
    Node(const K & k, const V & v) : left(NULL), right(NULL), key(k), value(v) {}
    Node(const K & k, const V & v, Node * l, Node * r) :
        left(l),
        right(r),
        key(k),
        value(v) {}
  };
  Node * root;

 public:
  friend void testit(void);

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const * cur = &root;
    while (*cur != NULL) {
      if ((*cur)->key == key) {
        return (*cur)->value;
      }
      else {
        if ((*cur)->key > key) {
          cur = &((*cur)->left);
        }
        else {
          cur = &((*cur)->right);
        }
      }
    }
    throw std::invalid_argument("can't find this key!");
  }

 private:
  Node * add_helper(const K & key, const V & value, Node * cur) {
    if (cur == NULL) {
      Node * ans = new Node(key, value, NULL, NULL);
      return ans;
    }
    else {
      if (cur->key == key) {
        cur->value = value;
      }
      else {
        if (cur->key > key) {
          Node * newleft = add_helper(key, value, cur->left);
          cur->left = newleft;
        }
        else {
          Node * newright = add_helper(key, value, cur->right);
          cur->right = newright;
        }
      }
      return cur;
    }
  }

 public:
  virtual void add(const K & key, const V & value) {
    root = add_helper(key, value, root);
  }

 private:
  Node * getMin(Node * node) {
    while (node->left != NULL) {
      node = node->left;
    }
    return node;
  }

  Node * removeMin(Node * node) {
    if (node->left == NULL) {
      Node * rightNode = node->right;
      delete node;
      return rightNode;
    }
    node->left = removeMin(node->left);
    return node;
  }

  Node * remove_helper(Node * node) {
    if (node->left == NULL) {
      Node * temp = node->right;
      delete node;
      return temp;
    }
    else if (node->right == NULL) {
      Node * temp = node->left;
      delete node;
      return temp;
    }
    else {
      Node * toRemove = getMin(node->right);
      K tempk = toRemove->key;
      V tempv = toRemove->value;
      node->key = tempk;
      node->value = tempv;
      node = removeMin(node->right);
      return node;
    }
  }

 public:
  Node ** find(K key) {
    Node ** cur = &root;
    while ((*cur) != NULL) {
      if ((*cur)->key == key) {
        return cur;
      }
      else {
        if ((*cur)->key > key) {
          cur = &((*cur)->left);
        }
        else {
          cur = &((*cur)->right);
        }
      }
    }
    return NULL;
  }

  virtual void remove(const K & key) {
    Node ** cur = find(key);
    if (cur != NULL) {
      *cur = remove_helper(*cur);
    }
    else {
      return;
    }
  }

 private:
  void printbst(Node * cur) {
    if (cur != NULL) {
      printbst(cur->left);
      std::cout << "(" << cur->key << ", " << cur->value << ")" << std::endl;
      printbst(cur->right);
    }
  }

 public:
  void printbst() {
    Node * cur = root;
    printbst(cur);
  }

 private:
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  void copy(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copy(current->left);
      copy(current->right);
    }
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) {
    Node * rhscur = rhs.root;
    if (rhscur != NULL) {
      copy(rhscur);
    }
    else {
      root = NULL;
    }
  }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp(rhs);
      destroy(root);
      root = NULL;
      //assert(temp.root != NULL);
      copy(temp.root);
      //std::swap(temp, *this);
    }
    return *this;
  }

  virtual ~BstMap() { destroy(root); }
};
