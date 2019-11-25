#include "commandshell.hpp"

void freecmd(size_t argc, char * args[]) {
  for (size_t i = 0; i < argc; i++) {
    free(args[i]);
  }
}
/*
size_t parse_command(char * line, char * args[]) {
  size_t i = 0;
  std::string command;
  while (line[i] != '\0') {
    if (line[i] == ' ') {
      if (i != 0 && line[i - 1] != ' ') {
        break;
      }
      else {
        i++;
      }
    }
    else {
      command.push_back(line[i]);
      i++;
    }
  }
  args[0] = strdup(command.c_str());
  return i;
}

size_t parse_args(char * line, size_t start, char * args[]) {
  size_t i = start;
  size_t argc = 1;
  while (line[i] != '\0') {
    if (line[i] == ' ') {
      i++;
    }
    else {
      size_t j = i;
      std::string arg;
      while (line[j] != '\0' && line[j] != ' ') {
        arg.push_back(line[j]);
        j++;
      }
      args[argc] = strdup(arg.c_str());
      argc++;
      i = j;
    }
  }
  return argc;
}
*/
/*
int quote_check(bool * quote_closed, size_t * quote_index, char * line) {
  *quote_closed = !(*quote_closed);
  if ((!quote_closed && *quote_index != 0 && line[*quote_index - 1] != ' ') ||
      (*quote_closed && line[*quote_index + 1] != '\0' &&
       line[*quote_index + 1] != ' ')) {
    std::cerr << "wrong position for quote mark!" << std::endl;
    return -1;
  }
  (*quote_index)++;
  if (line[*quote_index] == '\0') {
    return 0;
  }
  if (line[*quote_index] == '"') {
    *quote_closed = !(*quote_closed);
    (*quote_index)++;
    return 0;
  }
  return 1;
}
*/
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

int command_shell::ffosh() {
  while (true) {
    char * ECE551PATH = getenv("PATH");
    std::cout << "ffosh$";
    std::string command_string;
    std::getline(std::cin, command_string);
    char * command_line = strdup(command_string.c_str());
    if (!std::cin.good()) {
      free(command_line);
      break;
    }
    else if (!strcmp(command_line, "exit")) {
      free(command_line);
      break;
    }
    else {
      char * args[256];
      size_t argc = 0;
      if (parse(command_line, args, &argc)) {
        std::cerr << "command line format error!" << std::endl;
      }
      else {
        //for (size_t i = 0; i < argc; i++) {
        //std::cout << args[i] << std::endl;
        //}
        if (strchr(command_line, '/') == NULL) {
          search_and_exe<true>(argc, args, ECE551PATH);
        }
        else {
          search_and_exe<false>(argc, args, ECE551PATH);
        }
      }
      freecmd(argc, args);
    }
    free(command_line);
  }
  return EXIT_SUCCESS;
}

int main(void) {
  command_shell cs;
  cs.ffosh();
  return EXIT_SUCCESS;
}
/*
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

int command_shell::changedir(std::string * cur_dir, size_t argc, char * args[]) {
  if (argc != 2) {
    std::cerr << "wrong number of arguments for cd!" << std::endl;
    return EXIT_FAILURE;
  }
  if (chdir(args[1]) == -1) {
    std::perror("chdir");
    return EXIT_FAILURE;
  }
  else {
    get_cur_dir(cur_dir, args[1]);
    return EXIT_SUCCESS;
  }
}

int command_shell::setvar(std::string * line,
                          char * args[],
                          std::map<std::string, std::string> * vars) {
  if (strchr(args[1], '$') == NULL) {
    std::cerr << "var name not found in argument 1." << std::endl;
    return EXIT_FAILURE;
  }
  else {
  }
}

int command_shell::ffosh() {
  std::string cur_dir = "~/ece551/mp_miniproject";
  char * ECE551PATH = getenv("PATH");
  std::map<std::string, std::string> vars;
  while (true) {
    std::cout << "ffosh:" << cur_dir << " $";
    std::string command_string;
    std::getline(std::cin, command_string);
    char * command_line = strdup(command_string.c_str());
    if (!std::cin.good()) {
      free(command_line);
      break;
    }
    else if (!strcmp(command_line, "exit")) {
      free(command_line);
      break;
    }
    else {
      char * args[256];
      size_t argc = 0;
      if (parse(command_line, args, &argc)) {
        std::cerr << "command line format error!" << std::endl;
      }
      else {
        //for (size_t i = 0; i < argc; i++) {
        //std::cout << args[i] << std::endl;
        //}
        if (!strcmp(args[0], "cd")) {
          if (changedir(&cur_dir, argc, args)) {
            std::cerr << "change dir failed." << std::endl;
          }
        }
        else if (!strcmp(args[0], "set")) {
          setvar(&command_string, args, &vars);
        }
        else {
          if (strchr(command_line, '/') == NULL) {
            search_and_exe<true>(argc, args, ECE551PATH);
          }
          else {
            search_and_exe<false>(argc, args, ECE551PATH);
          }
        }
        freecmd(argc, args);
      }
      free(command_line);
    }
  }
  return EXIT_SUCCESS;
}

int main(void) {
  command_shell cs;
  cs.ffosh();
  return EXIT_SUCCESS;
}

 */
