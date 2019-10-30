#include <assert.h>

#include <iostream>

#include "il.h"
void testList() {
  IntList il1;
  IntList il2;

  for (int i = 1; i < 11; i++) {
    il1.addBack(i);
  }
  //=
  il2 = il1;
  assert(il2.getSize() == 10);

  //copy
  IntList il3(il1);
  assert(il3.getSize() == 10);

  //remove, find
  il1.remove(1);
  assert(il1.find(1) == -1);
  assert(il1.find(10) == 8);
  assert(il1.getSize() == 9);

  //head tail
  IntList il4;
  il4.addBack(1);
  il4.remove(1);
  assert(il4.head == NULL && il4.tail == NULL);

  il4.addFront(1);
  il4.remove(1);
  assert(il4.head == NULL && il4.tail == NULL);

  for (int i = 1; i <= 3; i++) {
    il4.addFront(i);
  }
  assert(il4.head->data == 3 && il4.tail->data == 1 && il4.head->next->data == 2 &&
         il4.tail->prev->data == 2);

  //=
  IntList il5;
  for (int i = 1; i <= 4; i++) {
    il5.addFront(i);
  }
  il5 = il4;
  assert(il5.head->data == 3 && il5.tail->data == 1 && il5.head->next->data == 2 &&
         il5.tail->prev->data == 2);

  //more of remove
  IntList il6;
  for (int i = 1; i <= 3; i++) {
    il6.addBack(i);
  }
  il6.remove(2);
  assert(il6.head->data == 1 && il6.tail->data == 3 && il6.head->next->data == 3 &&
         il6.tail->prev->data == 1);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
