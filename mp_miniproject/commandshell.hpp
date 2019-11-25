#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
class command_shell {
  // const char* command;
  //int found;

 public:
  int ffosh(void);
  void execute(size_t argc, char * args[]);
  int parse(char * line, char * args[], size_t * argc);
  int changedir(size_t argc, char * args[]);
  int setvar(char * line,
             size_t argc,
             char * args[],
             std::map<std::string, std::string> * vars);
  void parsevar(size_t argc, char * args[], std::map<std::string, std::string> vars);

  template<bool search_path>
  void search_and_exe(size_t argc, char * args[], const char * path) {
    size_t i = 0;
    int found = 0;
    std::ifstream ifs;
    if (search_path) {
      while (path[i] != '\0') {
        std::string temp;
        while (path[i] != ':' && path[i + 1] != '\0') {
          temp.push_back(path[i]);
          i++;
        }
        i++;
        temp.push_back('/');
        temp += args[0];
        ifs.open(temp.c_str());
        if (ifs.good()) {
          found = 1;
          ifs.close();
          free(args[0]);
          args[0] = strdup(temp.c_str());
          execute(argc, args);
          break;
        }
        else {
          ifs.clear();
        }
      }
      if (found == 0) {
        std::cerr << "Command " << args[0] << " not found" << std::endl;
      }
    }
    else {
      ifs.open(args[0]);
      if (ifs.good()) {
        ifs.close();
        execute(argc, args);
      }
      else {
        std::cerr << "Command " << args[0] << " not found" << std::endl;
      }
    }
  }

  //int has_slash(char * cmd);
  //void setfound(int n) { found = n; }
  //int getfound(void) { return found; }
  //void printstatus(void);
};
