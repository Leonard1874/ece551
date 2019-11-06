#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "bstset.h"
#include "set.h"

int main(void) {
  BstSet<int> bs1;

  int k[] = {33, 44, 12, 55, 99, 99, 16, 77, 0, -1, 100};
  for (int i = 0; i < 11; i++) {
    bs1.add(k[i]);
  }
  bs1.printbst();
  BstSet<int> bs4 = bs1;

  int v3[] = {33, 6, 12, 2, 99, 99, 8, 0, 8};

  for (int i = 0; i < 9; i++) {
    //std::cout << i << ", " << v2[i] << std::endl;
    bs1.remove(v3[i]);
  }

  int v4[] = {33, 44, 12, 55, 99, 99, 16, 77, 0, -1, 100, 110, 8};
  for (int i = 0; i < 13; i++) {
    //std::cout << i << ", " << v2[i] << std::endl;
    if (bs1.contains(v4[i]) == false) {
      std::cout << "did not find: " << v4[i] << std::endl;
    }
  }

  std::cout << "copying!" << std::endl;
  BstSet<int> bs2(bs1);
  bs2.printbst();

  std::cout << "=!" << std::endl;
  BstSet<int> bs3 = bs1;
  bs3.printbst();
  std::cout << "=!" << std::endl;
  bs3 = bs4;
  bs3.printbst();

  /*
  bs1.printbst();
  std::cout << "copying!" << std::endl;
  */
}
