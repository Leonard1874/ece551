#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
class command_shell {
  // const char* command;
  //int found;

 public:
  int ffosh(void);
  void execute(char * line);
  template<bool search_path>
  void search_and_exe(char * cmd, const char * path) {
    size_t i = 0;
    int found = 0;
    std::ifstream ifs;
    if (search_path) {
      while (path[i] != '\0') {
        char temp[256] = {};
        size_t j = 0;
        while (path[i] != ':' && path[i + 1] != '\0') {
          temp[j] = path[i];
          i++;
          j++;
        }
        i++;
        strcat(temp, "/");
        strcat(temp, cmd);
        ifs.open(temp);
        if (ifs.good()) {
          found = 1;
          ifs.close();
          execute(temp);
          break;
        }
        else {
          ifs.clear();
        }
      }
      if (found == 0) {
        std::cerr << "Command " << cmd << " not found" << std::endl;
      }
    }
    else {
      ifs.open(cmd);
      if (ifs.good()) {
        ifs.close();
        execute(cmd);
      }
      else {
        std::cerr << "Command " << cmd << " not found" << std::endl;
      }
    }
  }
  //  int parse(const char * line, char * args[]);

  //int has_slash(char * cmd);
  //void setfound(int n) { found = n; }
  //int getfound(void) { return found; }
  //void printstatus(void);
};
