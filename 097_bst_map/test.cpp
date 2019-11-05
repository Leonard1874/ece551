#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "bstmap.hpp"
#include "map.h"

int main(void) {
  BstMap<int, std::string> bm1;
  int k[] = {2, 4, 1, 7, 3, 9, -1, 88, 17, -23, 16, 44, 77};
  for (int i = 0; i < 13; i++) {
    bm1.add(k[i], "i");
  }
  bm1.printbst();
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
}
