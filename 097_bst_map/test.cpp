#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "bstmap.h"
#include "map.h"

void testit(void) {
  BstMap<int, int> bm1;

  int k[] = {33, 44, 12, 55, 99, 99, 16, 77, 0, -1, 100};
  for (int i = 0; i < 11; i++) {
    bm1.add(k[i], i);
  }
  bm1.printbst();
  std::cout << "copying!" << std::endl;
  BstMap<int, int> bm2(bm1);
  bm2.printbst();

  BstMap<int, int> bm3;

  int k1[] = {13, 48, 19, 75, 67, 16, 77, 99, -111, 150};
  for (int i = 0; i < 10; i++) {
    bm3.add(k1[i], i);
  }
  bm3.printbst();
  std::cout << "=" << std::endl;
  bm3 = bm1;
  bm3.printbst();
  /*
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

  int v1[] = {33, 44, 12, 55, 55, 99, 99, 16, 77, 0, -1, -101, 100};

  for (int i = 0; i < 13; i++) {
    // std::cout << i << ", " << v1[i] << std::endl;
    bm1.remove(v1[i]);
  }
  bm1.printbst();

  int v2[] = {77, 3, 17, 1, -23, 88, 7, 9, 44, 4};
  for (int i = 0; i < 10; i++) {
    //std::cout << i << ", " << v2[i] << std::endl;
    bm1.add(v2[i], i);
  }

  bm1.printbst();
  int v3[] = {5, 6, 1, 2, 3, 8, 8, 8, 8};

  for (int i = 0; i < 9; i++) {
    //std::cout << i << ", " << v2[i] << std::endl;
    bm1.remove(v3[i]);
  }

  bm1.printbst();
  int v4[] = {77, 3, 17, 1, -23, 88, 7, 9, 44, 4};
  for (int i = 0; i < 10; i++) {
    //std::cout << i << ", " << v2[i] << std::endl;
    bm1.add(v4[i], i);
  }

  bm1.printbst();
  */
  /*
  BstMap<int, int> bm2;

  int k2[] = {8, 8, 8};
  for (int i = 0; i < 3; i++) {
    bm2.add(k2[i], 0);
  }

  bm2.printbst();
  int v2[] = {5, 6, 1, 2, 3, 8, 8, 8, 8};

  for (int i = 0; i < 9; i++) {
    std::cout << i << ", " << v2[i] << std::endl;
    bm2.remove(v2[i]);
    bm2.printbst();
  }
  bm1.printbst();
  */
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
  /*
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
  /*
  int v[] = {1, 2, 3, 3, 4, 12};
  for (int i = 0; i < 6; i++) {
    std::cout << i << ", " << v[i] << std::endl;
    bm1.remove(v[i]);
    bm1.printbst();
  }
  */
  //int v2[] = {33, 44, 12, 55, 99, 99, 16, 77, 0, -1, 100};
}

int main(void) {
  // testit();
  BstMap<int, int> bm1;

  int k[] = {33, 44, 12, 55, 99, 99, 16, 77, 0, -1, 100};
  for (int i = 0; i < 11; i++) {
    bm1.add(k[i], i);
  }
  bm1.printbst();
  std::cout << "copying!" << std::endl;
  BstMap<int, int> bm2(bm1);
  bm2.printbst();

  BstMap<int, int> bm3;

  int k1[] = {13, 48, 19, 75, 67, 16, 77, 99, -111, 150};
  for (int i = 0; i < 10; i++) {
    bm3.add(k1[i], i);
  }
  bm3.printbst();
  std::cout << "=" << std::endl;
  bm3 = bm1;
  bm3.printbst();
  return EXIT_SUCCESS;
}
