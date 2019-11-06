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
    Node * cur = root;
    while (cur != NULL) {
      if (cur->key == key) {
        return cur->value;
      }
      else {
        if (cur->key > key) {
          cur = cur->left;
        }
        else {
          cur = cur->right;
        }
      }
    }
    throw std::invalid_argument("can't find this key!");
  }

 private:
  Node * add_helper(const K & key, const V & value, Node * cur) {
    if (cur == NULL) {
      cur = new Node(key, value, NULL, NULL);
      return cur;
    }
    else {
      if (cur->key == key) {
        cur->value = value;
      }
      else {
        if (cur->key > key) {
          cur->left = add_helper(key, value, cur->left);
        }
        else {
          cur->right = add_helper(key, value, cur->right);
        }
      }
      return cur;
    }
  }

 public:
  virtual void add(const K & key, const V & value) {
    root = add_helper(key, value, root);
  }

  Node * getMin(Node * cur) {
    if (cur->left == NULL)
      return cur;

    return getMin(cur->left);
  }

  Node * getMax(Node * cur) {
    if (cur->right == NULL)
      return cur;

    return getMax(cur->right);
  }

  Node * removeMin(Node * cur) {
    if (cur->left == NULL) {
      Node * newhead = cur->right;
      delete cur;
      return newhead;
    }

    cur->left = removeMin(cur->left);
    return cur;
  }

  Node * removeMax(Node * cur) {
    if (cur->right == NULL) {
      Node * newhead = cur->left;
      delete cur;
      return newhead;
    }

    cur->right = removeMax(cur->right);
    return cur;
  }

 private:
  Node * remove_helper(const K & key, Node * cur) {
    if (cur == NULL) {
      return cur;
    }
    if (cur->key == key) {
      if (cur->left == NULL && cur->right == NULL) {
        delete cur;
        return NULL;
      }
      else {
        if (cur->left == NULL) {
          Node * newhead = cur->right;
          delete cur;
          return newhead;
        }
        else if (cur->right == NULL) {
          Node * newhead = cur->left;
          delete cur;
          return newhead;
        }
        else {
          Node * getmin = getMin(cur->right);
          Node * replace = new Node(getmin->key, getmin->value);
          replace->right = removeMin(cur->right);
          replace->left = cur->left;
          delete cur;
          return replace;
        }
      }
    }
    else {
      if (cur->key > key) {
        cur->left = remove_helper(key, cur->left);
        return cur;
      }
      else {
        cur->right = remove_helper(key, cur->right);
        return cur;
      }
    }
  }

 public:
  virtual void remove(const K & key) { root = remove_helper(key, root); }

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

 public:
  BstMap() : root(NULL) {}
  virtual ~BstMap() {
    Node * current = root;
    destroy(current);
  }
};
/*
Node * getMin(Node * cur) {
    if (cur->left == NULL)
      return cur;

    return getMin(cur->left);
  }

  Node * getMax(Node * cur) {
    if (cur->right == NULL)
      return cur;

    return getMax(cur->right);
  }

  Node * removeMin(Node * cur) {
    if (cur->left == NULL) {
      Node * rightNode = cur->right;
      delete cur;
      return rightNode;
    }

    cur->left = removeMin(cur->left);
    return cur;
  }

  Node * removeMax(Node * cur) {
    if (cur->right == NULL) {
      Node * leftNode = cur->left;
      delete cur;
      return leftNode;
    }

    cur->right = removeMax(cur->right);
    return cur;
  }

if (cur == NULL) {
      return cur;
    }
    if (cur->key == key) {
      if (cur->left != NULL && cur->right != NULL) {
        Node * toReplace = getMax(cur->left);
        Node * Replace = new Node(toReplace->key, toReplace->value);
        Replace->left = removeMax(Replace->left);
        Replace->right = cur->right;
        delete cur;
        return Replace;
      }
      else {
        if (cur->left == NULL && cur->right == NULL) {
          delete cur;
          return NULL;
        }
        else {
          if (cur->left == NULL && cur->right != NULL) {
            Node * newhead = cur->right;
            delete cur;
            return newhead;
          }
          else {
            Node * newhead = cur->left;
            delete cur;
            return newhead;
          }
        }
      }
    }
    else {
      if (cur->key > key) {
        cur->left = remove_helper(key, cur->left);
        return cur;
      }
      else {
        cur->right = remove_helper(key, cur->right);
        return cur;
      }
    }
    root = remove_helper(key, root);
 */
