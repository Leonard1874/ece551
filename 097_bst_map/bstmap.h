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
      Node * temp = node->right;
      delete node;
      return temp;
    }
    else {
      node->left = removeMin(node->left);
      return node;
    }
  }

  Node * remove_helper(const K & key, Node * node) {
    if (node == NULL) {
      return NULL;
    }
    if (node->key > key) {
      node->left = remove_helper(key, node->left);
      return node;
    }
    else if (node->key < key) {
      node->right = remove_helper(key, node->right);
      return node;
    }
    else {
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

        Node * replace = new Node(tempk, tempv);

        replace->right = removeMin(node->right);
        replace->left = node->left;

        delete node;

        return replace;
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

  void copy(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copy(current->left);
      copy(current->right);
    }
  }

  void copy_e(Node * current) {
    if (current != NULL) {
      add(current->key, current->value);
      copy_e(current->left);
      copy_e(current->right);
    }
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) {
    if (rhs.root != NULL) {
      copy(rhs.root);
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
      copy_e(temp.root);
    }
    return *this;
  }

  virtual ~BstMap() { destroy(root); }
};

/*
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    Node * parent;
    Node * left;
    Node * right;
    K key;
    V value;
    Node() : left(NULL), right(NULL), key(NULL), value(NULL) {}
    Node(const K & k, const V & v) :
        parent(NULL),
        left(NULL),
        right(NULL),
        key(k),
        value(v) {}
    Node(const K & k, const V & v, Node * p, Node * l, Node * r) :
        parent(p),
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
  void remove_helper(Node * R) {
    //assert(R->parent != NULL);
    if (R->left == NULL && R->right == NULL && R->parent != NULL) {
      if (R->parent->left == R) {
        R->parent->left = NULL;
        R->left = NULL;
        R->right = NULL;
        R->parent = NULL;
        delete R;
        return;
      }
      else {
        R->parent->right = NULL;
        R->left = NULL;
        R->right = NULL;
        R->parent = NULL;
        delete R;
        return;
      }
    }
    else {
      if (R->left == NULL && R->right != NULL && R->parent != NULL) {
        if (R->parent->left == R) {
          R->parent->left = R->right;
          R->right->parent = R->parent;
          R->left = NULL;
          R->right = NULL;
          R->parent = NULL;
          delete R;
          return;
        }
        else {
          R->parent->right = R->right;
          R->right->parent = R->parent;
          R->left = NULL;
          R->right = NULL;
          R->parent = NULL;
          delete R;
          return;
        }
      }
      else if (R->right == NULL && R->left != NULL && R->parent != NULL) {
        if (R->parent->left == R) {
          R->parent->left = R->left;
          R->left->parent = R->parent;
          R->left = NULL;
          R->right = NULL;
          R->parent = NULL;
          delete R;
          return;
        }
        else {
          R->parent->right = R->left;
          R->left->parent = R->parent;
          R->left = NULL;
          R->right = NULL;
          R->parent = NULL;
          delete R;
          return;
        }
      }
      else {
        std::cerr << "cannpt handle!" << std::endl;
      }
    }
  }

 public:
  Node * find(Node * cur, K key) {
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
    return cur;
  }

  virtual void remove(const K & key) {
    Node * cur = root;
    cur = find(root, key);
    if (cur == NULL) {
      std::cerr << "not such node" << std::endl;
      return;
    }
    else {
      if (cur->left != NULL && cur->right != NULL) {
        Node * toRemove = cur;
        toRemove = cur->left;
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
          if (root->right == NULL && root->left == NULL) {
            delete root;
            root = NULL;
            return;
          }
          else {
            if (root->right != NULL) {
              root = root->right;
              root->parent = NULL;
              cur->left = NULL;
              cur->right = NULL;
              delete cur;
              return;
            }
            else {
              root = root->left;
              root->parent = NULL;
              cur->left = NULL;
              cur->right = NULL;
              delete cur;
              return;
            }
          }
        }
        else {
          Node * toRemove = cur;
          remove_helper(toRemove);
        }
      }
    }
  }

 private:
  void printbst(Node * cur) {
    if (cur != NULL) {
      assert(cur == root || cur->parent != NULL);
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


*/
