#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "bstmap.hpp"
#include "map.h"

void testit(void) {
  /*
  assert(bm1.root == NULL);
  bm1.printbst();
  int v2[] = {77, 3, 17, 1, -23, 88, 7, 9, 44, 4};
  for (int i = 0; i < 10; i++) {
    std::cout << i << ", " << v2[i] << std::endl;
    bm1.remove(v2[i]);
    bm1.printbst();
  }
  */
  /*
  bm1.printbst();
  for (int j = 0; j < 10; j++) {
    try {
      std::cout << bm1.lookup(k[j]) << std::endl;
    }
    catch (std::invalid_argument & e) {
      std::cout << e.what() << std::endl;
    }
  }
  try {
    std::cout << bm1.lookup(88) << std::endl;
  }
  catch (std::invalid_argument & e) {
    std::cout << e.what() << std::endl;
  }
  */
  //bm1.remove(100);

  //bm1.printbst();
  /*
  bm1.remove(2);
  bm1.remove(16);
  bm1.remove(-1);
  bm1.printbst();
  try {
    std::cout << bm1.lookup(3) << std::endl;
  }
  catch (std::invalid_argument & e) {
    std::cout << e.what() << std::endl;
  }
  
  int v[] = {77, 3, 17, 1, -23, 88, 7, 9, 44, 4};
  for (int i = 0; i < 10; i++) {
    std::cout << i << ", " << v[i] << std::endl;
    bm1.remove(v[i]);
  }
  */
}

int main(void) {
  // testit();
  BstMap<int, int> bm1;

  int k[] = {1, 2, 3, 4};
  for (int i = 0; i < 4; i++) {
    bm1.add(k[i], i);
  }

  int v[] = {1, 2, 3, 3, 4};
  for (int i = 0; i < 5; i++) {
    std::cout << i << ", " << v[i] << std::endl;
    bm1.remove(v[i]);
    bm1.printbst();
  }
  return EXIT_SUCCESS;
}