#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
/*
template<typename T>
class iolines {
 private:
  std::vector<T> lines;
  int num;

 public:
  iolines() : lines(NULL), num(0) {}
  template<typename X>
  friend std::ostream & operator<<(std::ostream & s, const iolines<X> & x);
};*/
/*
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & x) {
  return s << x.lines;
}
*/
void printvec(const std::vector<std::string> & lines) {
  for (size_t i = 0; i < lines.size(); i++) {
    std::cout << lines[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  std::vector<std::string> lines;
  std::string line;
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifs(argv[i]);
      if (ifs.good()) {
        while (getline(ifs, line).good()) {
          lines.push_back(line);
        }
        std::sort(lines.begin(), lines.end());
        printvec(lines);
      }
      else {
        std::cerr << "cannot open file!\n";
        ifs.clear();
        return EXIT_FAILURE;
      }
    }
  }
  else {
    while (std::cin.good()) {
      getline(std::cin, line);
      lines.push_back(line);
    }
    std::sort(lines.begin(), lines.end());
    printvec(lines);
  }
  return EXIT_SUCCESS;
}
