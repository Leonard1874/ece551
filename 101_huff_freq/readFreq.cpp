#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <map>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream ifs(fname);
  uint64_t * ans = new uint64_t[257];
  for (uint64_t i = 0; i < 256; i++) {
    ans[i] = 0;
  }
  int c;
  while (ifs.good()) {
    c = ifs.get();
    if (c >= 0 && c <= 256) {
      ++ans[c];
    }
  }
  ifs.close();
  ans[256] = 1;
  return ans;
}
