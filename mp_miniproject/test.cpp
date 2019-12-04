#include <cstdlib>
#include <cstring>
#include <iostream>

int main(int argc, char ** argv) {
  std::cout << argc << std::endl;
  if (!strcmp(argv[1], "fail")) {
    return EXIT_FAILURE;
  }
  else if (!strcmp(argv[1], "seg")) {
    char * n = NULL;
    (*n) += 1;
  }
  else {
    for (int i = 0; i < argc; i++) {
      std::cout << argv[i + 1] << std::endl;
    }
    return EXIT_SUCCESS;
  }
}
