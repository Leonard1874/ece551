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
#include <vector>
extern char ** environ;  //get environment variables from system

/*This is the abstracted class of this command shell,
most functions are declared here and implemented in .cpp file, 
except for two templated functions. */

class command_shell {
 public:
  /* step 1 */
  int ffosh(void);  // top level function for the shell

  void execute(size_t argc, char * args[], char * envs[]);  // fork, execve, waitpid

  /* step 2 */

  /*This function is used for searching command in PATH and call execute for the command. 
    It is templated for two situations: if search_path is true, search ECE551PATH for command, 
    if false, use the absolute path for the command directly. */

  template<bool search_path>
  void search_and_exe(size_t argc, char * args[], std::string & path, char ** envs) {
    // ifstream is used here to check if the path for the command is valid
    std::ifstream ifs;

    //search ECE551PATH
    if (search_path) {
      size_t i = 0;
      bool found = false;

      //parse ECE551PATH, generate possible path for the command
      while (path[i] != '\0') {
        std::string temp;
        //get each directory to search (separated by ':')
        while (path[i] != ':' && path[i + 1] != '\0') {
          temp.push_back(path[i]);
          i++;
        }
        i++;
        //append the command name to each directory to form a possible path
        temp.push_back('/');
        temp += args[0];

        //check if the path is valid by trying to open it
        ifs.open(temp.c_str());
        if (ifs.good()) {
          found = true;
          ifs.close();
          free(args[0]);
          args[0] = strdup(temp.c_str());
          execute(argc, args, envs);
          break;
        }
        else {
          ifs.clear();
        }
      }
      if (!found) {
        std::cerr << "Command " << args[0] << " not found" << std::endl;
      }
    }

    //use the absolute path directly
    else {
      // check if the path is valid
      ifs.open(args[0]);
      if (ifs.good()) {
        ifs.close();
        execute(argc, args, envs);
      }
      else {
        std::cerr << "Command " << args[0] << " not found" << std::endl;
      }
    }
  }

  int parse(char * line,
            std::vector<std::string> & argv,
            size_t * argc);  //parse the command line, search for arguments

  /* step 3 */
  int changedir(size_t argc, char * args[]);  // build in command 'cd'

  void parsevar(
      size_t argc,
      char * args[],
      std::map<std::string, std::string> & vars,
      std::map<std::string, std::string> & envm);  // extract varname and var value

  int setvar(char * line,
             size_t argc,
             char * args[],
             std::map<std::string, std::string> & vars);  // build in command 'set'

  void init_env(std::vector<std::string> & envv);  //initialize envirionment variables

  void update_env(
      std::map<std::string, std::string> & vars,
      std::string & varname,
      std::vector<std::string> & envv);  //helper of 'export_rev', export var value to env

  void var_rev(std::map<std::string, std::string> & vars,
               std::string & varname);  //helper of 'export_rev', reverse var value

  /* This function is for build in command 'export' and 'rev':
    templated, template true, function as export, false, function as rev. */
  template<bool to_export>
  int export_rev(std::vector<std::string> & envv,
                 std::map<std::string, std::string> & vars,
                 size_t argc,
                 char * args[]) {
    // check argument number, only accept 1 argument
    if (argc != 2) {
      std::cerr << "wrong number of argument for export/rev." << std::endl;
      return EXIT_FAILURE;
    }

    else {
      // parse variable name in the argument
      std::string varname = "";
      size_t i = 0;
      while (args[1][i] != '\0') {
        if (isalpha(args[1][i]) || isdigit(args[1][i]) || args[1][i] == '_') {
          varname.push_back(args[1][i]);
          i++;
        }
        else {
          std::cerr << "illeagal character in varname!" << std::endl;
          return EXIT_FAILURE;
        }
      }
      // to export/rev, variable must be set before (in record of set)
      if (vars.count(varname) != 0) {
        if (to_export) {
          update_env(vars, varname, envv);  // export to env
        }
        else {
          var_rev(vars, varname);  // reverse var value
        }
      }
      else {
        std::cerr << "varname not exist" << std::endl;
      }
    }
    return EXIT_SUCCESS;
  }
};
