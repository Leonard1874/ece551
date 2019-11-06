#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  class Node {
   public:
    Node * left;
    Node * right;
    T key;
    Node() : left(NULL), right(NULL), key(NULL) {}
    Node(const T & k) : left(NULL), right(NULL), key(k) {}
    Node(const T & k, Node * l, Node * r) : left(l), right(r), key(k) {}
  };
  Node * root;

 public:
  friend void testit(void);

  virtual bool contains(const T & key) const {
    Node * const * cur = &root;
    while (*cur != NULL) {
      if ((*cur)->key == key) {
        return true;
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
    return false;
  }

 private:
  Node * add_helper(const T & key, Node * cur) {
    if (cur == NULL) {
      Node * ans = new Node(key, NULL, NULL);
      return ans;
    }
    else {
      if (cur->key == key) {
        cur->key = key;
      }
      else {
        if (cur->key > key) {
          Node * newleft = add_helper(key, cur->left);
          cur->left = newleft;
        }
        else {
          Node * newright = add_helper(key, cur->right);
          cur->right = newright;
        }
      }
      return cur;
    }
  }

 public:
  virtual void add(const T & key) { root = add_helper(key, root); }

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

  Node * remove_helper(const T & key, Node * node) {
    if (node == NULL)
      return NULL;

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
        T tempk = toRemove->key;
        Node * replace = new Node(tempk);
        replace->right = removeMin(node->right);
        replace->left = node->left;
        delete node;
        return replace;
      }
    }
  }

 public:
  virtual void remove(const T & key) { root = remove_helper(key, root); }

 private:
  void printbst(Node * cur) {
    if (cur != NULL) {
      printbst(cur->left);
      std::cout << "(" << cur->key << ")" << std::endl;
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
      add(current->key);
      copy(current->left);
      copy(current->right);
    }
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) : root(NULL) {
    if (rhs.root != NULL) {
      copy(rhs.root);
    }
    else {
      root = NULL;
    }
  }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet<T> temp(rhs);
      destroy(root);
      root = NULL;
      copy(temp.root);
    }
    return *this;
  }

  virtual ~BstSet() { destroy(root); }
};
