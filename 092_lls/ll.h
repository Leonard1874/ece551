#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * previous;
    Node() : data(0), next(NULL), previous(NULL) {}
    Node(const T & item) : data(item), next(NULL), previous(NULL) {}
    Node(const T & item, Node * n) : data(item), next(n), previous(NULL) {}
    Node(const T & item, Node * n, Node * p) : data(item), next(n), previous(p) {}
    ~Node() {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  void addFront(const T & item) {
    head = new Node(item, head);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->previous = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->previous->next = tail;
    }
    size++;
  }
  int find(const T & item) const {
    Node * current = head;
    for (int i = 0; i < size; i++) {
      if (current->data == item) {
        return i;
      }
      current = current->next;
    }
    return -1;
  }

  Node * remove(const T & data, Node * current) {
    if (current == NULL) {
      return NULL;
    }
    if (data == current->data) {
      Node * ans = current->next;
      delete current;
      return ans;
    }
    current->next = remove(data, current->next);
    return current;
  }

  bool remove(const T & item) {
    if (find(item) == -1) {
      return false;
    }
    else {
      head = remove(item, head);
      size--;
      return true;
    }
  }

  T & operator[](int index) {
    assert(index >= 0 && index <= size - 1 && head != NULL);
    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  const T & operator[](int index) const {
    assert(index >= 0 && index <= size - 1 && head != NULL);
    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  int getSize() const { return size; }

  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(rhs.getSize()) {
    for (int i = 0; i < size; i++) {
      tail = new Node(rhs[i], NULL, tail);
      if (head == NULL) {
        head = tail;
      }
      else {
        tail->previous->next = tail;
      }
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      Node * temphead = NULL;
      Node * temptail = NULL;

      for (int i = 0; i < rhs.getSize(); i++) {
        temphead = new Node(rhs[i], temphead);
        if (temptail == NULL) {
          temptail = temphead;
        }
        else {
          temphead->next->previous = temphead;
        }
      }

      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      head = temphead;
      tail = temptail;
      size = rhs.getSize();
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
};

#endif
/*
  bool remove(const T & item) {
    if (head == NULL) {
      return false;
    }
    if (head->data == item) {
      if (tail == head) {
        delete head;
        size--;
        tail = NULL;
        return true;
      }
      else {
        Node * temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
      }
    }
    Node * cur = head;
    while (cur->next != NULL) {
      if (cur->next->data == item) {
        if (cur->next != tail) {
          Node * temp = cur->next;
          cur->next = cur->next->next;
          cur->next->previous = temp->previous;
          delete temp;
          size--;
          return true;
        }
        else {
          tail = cur;
          Node * temp = cur->next;
          cur->next = NULL;
          delete temp;
          size--;
          return true;
        }
      }
      cur = cur->next;
    }
    return false;
  }
  */
/*
  bool remove(const T & item) {
    Node ** current = &head;
    bool res = false;
    while (*current != NULL) {
      if ((*current)->data == item) {
        Node * temp = *current;
        if (temp->next != NULL) {
          *current = (*current)->next;
          temp->next->previous = temp->previous;
          delete temp;
        }
        else {
          tail = temp->previous;
          delete temp;
          *current = NULL;
        }
        size--;
        res = true;
        return res;
      }
      current = &((*current)->next);
    }
    return res;
  }
  */
/*
 Node * temphead = NULL;
      Node * temptail = NULL;

      for (int i = 0; i < rhs.getSize(); i++) {
        temphead = new Node(rhs[i], temphead);
        if (temptail == NULL) {
          temptail = temphead;
        }
        else {
          temphead->next->previous = temphead;
        }
      }

      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      head = temphead;
      tail = temptail;
      size = rhs.getSize();
*/
