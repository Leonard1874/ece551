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
          Node * replace =
              new Node(getmin->key, getmin->value, getmin->left, getmin->right);
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
  virtual ~BstMap() { destroy(root); }
};
/*
    Node * cur = root;
    while (cur != NULL) {
      if (cur->key == key) {
        break;
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
    if (cur == NULL) {
      std::cerr << "not such node" << std::endl;
      return;
    }
    else {
      if (cur->left != NULL && cur->right != NULL) {
        Node * toRemove = cur;
        toRemove = toRemove->left;
        while (toRemove->right != NULL) {
          toRemove = toRemove->right;
        }
        K tmp1 = cur->key;
        V tmp2 = cur->value;
        cur->key = toRemove->key;
        cur->value = toRemove->value;
        toRemove->key = tmp1;
        toRemove->value = tmp2;
        remove_helper(toRemove);
      }
      else {
        if (cur == root) {
          if (cur->right == NULL && cur->left == NULL) {
            delete cur;
            root = NULL;
          }
          else {
            if (cur->right != NULL) {
              cur = cur->right;
              cur->parent = NULL;
              delete root;
              root = cur;
            }
            else {
              cur = cur->left;
              cur->parent = NULL;
              delete root;
              root = cur;
            }
          }
        }
        else {
          Node * toRemove = cur;
          remove_helper(toRemove);
        }
      }
    }
    */
/*
    if (R->left == NULL && R->right == NULL) {
      if (R->parent->left == R) {
        R->parent->left = NULL;
        delete R;
        return;
      }
      if (R->parent->right == R) {
        R->parent->right = NULL;
        delete R;
        return;
      }
    }
    if (R->left == NULL) {
      if (R->parent->left == R) {
        R->parent->left = R->right;
        R->right->parent = R->parent;
        delete R;
        return;
      }
      if (R->parent->right == R) {
        R->parent->right = R->right;
        R->right->parent = R->parent;
        delete R;
        return;
      }
    }
    if (R->right == NULL) {
      if (R->parent->left == R) {
        R->parent->left = R->left;
        R->left->parent = R->parent;
        delete R;
        return;
      }
      if (R->parent->right == R) {
        R->parent->right = R->left;
        R->left->parent = R->parent;
        delete R;
        return;
      }
    }
    */
