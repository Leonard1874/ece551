#include "commandshell.hpp"

void freecmd(size_t argc, char * args[]) {
  for (size_t i = 0; i < argc; i++) {
    free(args[i]);
  }
}

int command_shell::parse(char * line, char * args[], size_t * argc) {
  size_t i = 0;
  bool isempty = true;
  bool quote_closed = true;
  bool escaping = false;
  while (line[i] != '\0') {
    if (line[i] == ' ') {
      i++;
    }
    else {
      size_t j = i;
      std::string arg;
      while (line[j] != '\0') {
        if (line[j] == '"' && !escaping) {
          quote_closed = !quote_closed;
          j++;
          if (line[j] == '\0') {
            break;
          }
          if (line[j] == '"') {
            quote_closed = !(quote_closed);
            j++;
            break;
          }
        }

        if (line[j] == '\\') {
          if (line[j + 1] == '\0' || (line[j + 1] != '"' && line[j + 1] != '\\')) {
            std::cerr << "unknown gramma of \\, only \" and \\ is allowed." << std::endl;
            return EXIT_FAILURE;
          }
          else {
            escaping = true;
            j++;
          }
        }

        if (quote_closed && (line[j] == ' ' || line[j] == '\0')) {
          break;
        }
        arg.push_back(line[j]);
        if (*argc == 0 && line[j] != ' ') {
          isempty = false;
        }
        if (line[j] == '"' || line[j] == '\\') {
          escaping = false;
        }
        j++;
      }
      if (!arg.empty()) {
        args[*argc] = strdup(arg.c_str());
        (*argc)++;
      }
      i = j;
    }
  }
  if (isempty) {
    std::cerr << "empty command!" << std::endl;
    return EXIT_FAILURE;
  }
  if (!quote_closed) {
    std::cerr << "quote unclosed!" << std::endl;
    return EXIT_FAILURE;
  }
  else {
    return EXIT_SUCCESS;
  }
}

void command_shell::execute(size_t argc, char * args[]) {
  pid_t cpid, w;
  int wstatus = 0;
  char * envs[] = {NULL};
  args[argc] = NULL;
  cpid = fork();
  if (cpid == -1) {
    std::perror("fork fault");
    exit(EXIT_FAILURE);
  }
  else if (cpid == 0) {
    execve(args[0], args, envs);
    std::perror("execve fault");
    freecmd(argc, args);
    exit(EXIT_FAILURE);
  }
  else {
    w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
    if (w == -1) {
      std::perror("waitpid fault");
      exit(EXIT_FAILURE);
    }
    else {
      if (WIFEXITED(wstatus)) {
        if (WEXITSTATUS(wstatus) == 0) {
          std::cout << "Program was successful" << std::endl;
        }
        else {
          std::cerr << "Program failed with code " << WEXITSTATUS(wstatus) << std::endl;
        }
      }
      if (WIFSIGNALED(wstatus)) {
        std::cerr << "Terminated by signal " << WTERMSIG(wstatus) << std::endl;
      }
    }
  }
}

/*
void get_cur_dir(std::string * cur_dir, char * path) {
  size_t i = 0;
  while (path[i] != '\0') {
    std::string path_section = "";
    size_t j = i;
    while (path[j] != '/' && path[j] != '\0') {
      path_section.push_back(path[j]);
      j++;
    }
    if (path_section == ".") {
      *cur_dir = *cur_dir;
    }
    else if (path_section == "..") {
      size_t last_slash = (*cur_dir).find_last_of("/");
      (*cur_dir).erase(last_slash, (*cur_dir).length());
    }
    else {
      (*cur_dir).push_back('/');
      (*cur_dir).append(path_section);
    }
    if (path[j] != '\0') {
      j++;
      i = j;
    }
    else {
      i = j;
    }
  }
}
*/
int command_shell::changedir(size_t argc, char * args[]) {
  if (argc != 2) {
    std::cerr << "wrong number of arguments for cd!" << std::endl;
    return EXIT_FAILURE;
  }
  if (chdir(args[1]) == -1) {
    std::perror("chdir");
    return EXIT_FAILURE;
  }
  else {
    return EXIT_SUCCESS;
  }
}
/*
void set_parsevar(char * line, std::string * varname, std::string * varval) {
  size_t i = 0;
  while (line[i] != '\0') {
    if (line[i] != '$') {
      i++;
    }
    else {
      size_t j = i + 1;
      while (line[j] != '\0') {
        if (isalpha(line[j]) || isdigit(line[j]) || line[j] == '_') {
          (*varname).push_back(line[j]);
          j++;
        }
        else {
          break;
        }
      }
      while (line[j] != '\0') {
        (*varval).push_back(line[j]);
        j++;
      }
      i = j;
    }
  }
}
*/

int command_shell::setvar(char * line,
                          size_t argc,
                          char * args[],
                          std::map<std::string, std::string> * vars) {
  if (argc < 2) {
    std::cerr << "wrong number of argument for set." << std::endl;
    return EXIT_FAILURE;
  }
  else {
    std::string varname = "";
    std::string varval = "";
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
    char * start = strstr(line, args[1]);
    size_t j = start - line + varname.length();
    while (line[j] != '\0') {
      varval.push_back(line[j]);
      j++;
    }
    //std::cout << varname << ", " << varval << std::endl;
    (*vars)[varname] = varval;
  }
  return EXIT_SUCCESS;
}

void command_shell::parsevar(size_t argc,
                             char * args[],
                             std::map<std::string, std::string> vars) {
  size_t i = 1;
  if (argc < 2) {
    return;
  }
  while (i < argc) {
    if (strchr(args[i], '$') == NULL) {
      i++;
    }
    else {
      std::string temp = "";
      size_t j = 0;
      while (args[i][j] != '\0') {
        if (args[i][j] != '$') {
          temp.push_back(args[i][j]);
          j++;
        }
        else {
          std::string varname;
          size_t k = j + 1;
          while (args[i][k] != '\0') {
            if (isalpha(args[i][k]) || isdigit(args[i][k]) || args[i][k] == '_') {
              varname.push_back(args[i][k]);
              k++;
            }
            else {
              break;
            }
          }
          if (vars.count(varname) != 0) {
            temp.append(vars[varname]);
          }
          else {
            temp.push_back('$');
            temp.append(varname);
          }
          j = k;
        }
      }
      std::cout << temp << std::endl;
      free(args[i]);
      args[i] = strdup(temp.c_str());
      i++;
    }
  }
}

int command_shell::ffosh() {
  char * ECE551PATH = getenv("PATH");
  std::map<std::string, std::string> vars;
  std::map<std::string, std::string> envs;
  std::string path = ECE551PATH;
  vars["ECE551PATH"] = path;
  envs["ECE551PATH"] = path;
  /*
  size_t i = 0;
  while (ECE551PATH[i] != '\0') {
    path.push_back(ECE551PATH[i]);
    i++;
  }
  */
  //std::cout << path << std::endl;
  //std::cout << vars["ECE551PATH"] << ", " << envs["ECE551PATH"] << std::endl;
  while (true) {
    char * cur_dir = get_current_dir_name();
    std::cout << "ffosh:" << cur_dir << " $";
    std::string command_string;
    std::getline(std::cin, command_string);
    char * command_line = strdup(command_string.c_str());
    if (!std::cin.good()) {
      free(command_line);
      free(cur_dir);
      break;
    }
    else if (!strcmp(command_line, "exit")) {
      free(command_line);
      free(cur_dir);
      break;
    }
    else {
      char * args[256];
      size_t argc = 0;
      if (parse(command_line, args, &argc)) {
        std::cerr << "command line format error!" << std::endl;
      }
      else {
        parsevar(argc, args, vars);
        if (!strcmp(args[0], "cd")) {
          if (changedir(argc, args)) {
            std::cerr << "change dir failed." << std::endl;
          }
        }
        else if (!strcmp(args[0], "set")) {
          if (setvar(command_line, argc, args, &vars)) {
            std::cerr << "set varname failed" << std::endl;
          }
        }
        else {
          if (strchr(command_line, '/') == NULL) {
            search_and_exe<true>(argc, args, envs["ECE551PATH"].c_str());
          }
          else {
            search_and_exe<false>(argc, args, envs["ECE551PATH"].c_str());
          }
        }
      }
      freecmd(argc, args);
      free(command_line);
    }
    free(cur_dir);
  }
  return EXIT_SUCCESS;
}

int main(void) {
  command_shell cs;
  cs.ffosh();
  return EXIT_SUCCESS;
}
