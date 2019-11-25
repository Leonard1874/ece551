#include <cstdlib>
#include <iostream>

int main(int argc, char ** argv) {
  std::cout << "test!" << std::endl;
  for (int i = 0; i < argc; i++) {
    std::cout << argv[i + 1] << std::endl;
  }
  return EXIT_SUCCESS;
}
