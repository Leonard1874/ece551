#include "commandshell.hpp"

/* free allocated space */

/*This funcyion is used to free the space allocated for arguments*/
void freecmd(size_t c, char * s[]) {
  for (size_t i = 0; i < c; i++) {
    free(s[i]);
  }
  delete[] s;
}

/* step 1 */

/*This function is the execution part of the shell, use fork, execve and waitpid.
Inputs are argc: number of arguemnts, args: list of arguments, envs: list of envrionment vars.*/
void command_shell::execute(size_t argc, char * args[], char * envs[]) {
  pid_t cpid, w;
  int wstatus = 0;
  args[argc] = NULL;
  cpid = fork();
  if (cpid == -1) {
    std::perror("fork fault");
    exit(EXIT_FAILURE);
  }
  else if (cpid == 0) {
    execve(args[0], args, envs);
    std::perror("execve fault");
    // if execve fault, clear the allocated space in child process
    freecmd(argc, args);
    delete[] envs;
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

/* step 2 */

/* This function is used to parse the command line and extract arguments,
takes the command line as input, parse it and save arguments into agrs, count
argument number(argc). For rules of parsing, see README.*/
int command_shell::parse(char * line, std::vector<std::string> & argv, size_t * argc) {
  //flags
  bool isempty = true;       // if command line is empty
  bool quote_closed = true;  // if quotes are closed
  bool escaping = false;     // if escaping (\" \\) is valid

  //parsing
  size_t i = 0;
  while (line[i] != '\0') {
    if (line[i] == ' ') {  //skip whitespace
      i++;
    }
    else {
      size_t j = i;
      std::string arg;  //temporaryly save argument in arg
      while (line[j] != '\0') {
        if (line[j] == '"' && !escaping) {
          quote_closed =
              !quote_closed;  //each time there is a non-escaping ", update quote closed status
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

        if (line[j] == '\\') {  //process escaping
          if (line[j + 1] == '\0' || (line[j + 1] != '"' && line[j + 1] != '\\')) {
            std::cerr << "unknown gramma of \\, only \" and \\ is allowed." << std::endl;
            return EXIT_FAILURE;
          }
          else {
            escaping = true;  // escaping start
            j++;
          }
        }

        if (quote_closed && (line[j] == ' ' || line[j] == '\0')) {
          break;
        }
        arg.push_back(line[j]);  //current argument ends, break inner loop

        if (*argc == 0 && line[j] != ' ') {
          isempty = false;  //if the first part(command) of line is not empty, mark it
        }
        if (line[j] == '"' || line[j] == '\\') {
          escaping = false;  //get escaping value, escaping end
        }
        j++;
      }

      if (!arg.empty()) {
        argv.push_back(arg);  //if get a valid argument, save it in argv
        (*argc)++;
      }
      i = j;
    }
  }

  //output
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

/* step 3 */

/*This function is for command cd, call chdir, change directory and
report error if any.*/
int command_shell::changedir(size_t argc, char * args[]) {
  if (argc != 2) {
    std::cerr << "wrong number of arguments for cd!"
              << std::endl;  //check number of arguments, only accept 1 argument
    return EXIT_FAILURE;
  }
  if (chdir(args[1]) == -1) {
    std::perror("chdir");  // call chdir and output error if any
    return EXIT_FAILURE;
  }
  else {
    return EXIT_SUCCESS;
  }
}

/*This function is for parsing the command line and extract the
variable name in it, if there is any, replace var names with var
valuse.*/
void command_shell::parsevar(size_t argc,
                             char * args[],
                             std::map<std::string, std::string> & vars,
                             std::map<std::string, std::string> & envm) {
  if (argc < 2) {
    return;  //if there is not argument, return directly
  }

  size_t i = 1;
  while (i < argc) {
    if (strchr(args[i], '$') == NULL) {
      i++;  //move to the place where '$' appear
    }
    else {
      //use temp to save the new argument that should be placed into the command line
      std::string temp = "";
      size_t j = 0;
      while (args[i][j] != '\0') {
        if (args[i][j] != '$') {
          temp.push_back(args[i][j]);
          j++;
        }
        else {
          //use varname to save the parsed variable's name
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
          //if varname is a valid one save its value in temp
          if (vars.count(varname) != 0) {
            temp.append(vars[varname]);
          }
          else if (envm.count(varname) != 0) {
            temp.append(envm[varname]);
          }
          //if its not a valid one, save the varname itself
          else {
            temp.push_back('$');
            temp.append(varname);
          }
          j = k;
        }
      }
      free(args[i]);
      args[i] = strdup(temp.c_str());  //repalce the argument
      i++;
    }
  }
}

/*Helper function of setvar, parse the command line, get the value
for the variable and save it in varval.*/
void get_var_value(char * line, std::string & varval) {
  size_t x = 1;
  int countskip = 0;
  //skip the command, argument1 and spaces before the second argument, read in var value
  while (line[x] != '\0') {
    if (line[x] == ' ' && line[x - 1] != ' ') {
      countskip++;
    }
    if (countskip == 2) {
      break;
    }
    x++;
  }
  size_t j = x;
  while (line[j] != '\0') {
    if (line[j] != ' ') {
      break;
    }
    j++;
  }
  while (line[j] != '\0') {
    varval.push_back(line[j]);
    j++;
  }
}

/*This function is for setting the value of variables,
inputs are command line, parsed arguments and variable map,
get the value of variable and update the variable map*/
int command_shell::setvar(char * line,
                          size_t argc,
                          char * args[],
                          std::map<std::string, std::string> & vars) {
  //this command takes more than one arguments
  if (argc < 2) {
    std::cerr << "wrong number of argument for set." << std::endl;
    return EXIT_FAILURE;
  }
  else {
    //parse the first argument, get the variable name
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
    //parse the rest part of the line as the value of variable
    std::string varval = "";
    get_var_value(line, varval);
    //set var value
    vars[varname] = varval;
  }
  return EXIT_SUCCESS;
}

/*This function is used for processing data structures for arguments and envrionment variables.*/
void getenv_arg(char ** envs,
                char ** args,
                std::vector<std::string> & envv,
                std::vector<std::string> argv,
                std::map<std::string, std::string> envm) {
  // Envrionment variables: transfer from vector envv to map envm and char** envs.
  for (size_t i = 0; i < envv.size(); i++) {
    //transfer std::string in vector to char* in char**
    envs[i] = strdup(envv[i].c_str());
    //parse the std::string in vector and save env's name and its value to the map
    std::string envname;
    std::string envvalue;
    size_t j = 0;
    while (envv[i][j] != '=') {
      envname.push_back(envv[i][j]);
      j++;
    }
    size_t k = j + 1;
    while (envv[i][k] != '\0') {
      envvalue.push_back(envv[i][k]);
      k++;
    }
    envm[envname] = envvalue;
  }
  envs[envv.size()] = NULL;

  //Arguments: transfer from vector argv to char** args, then use args for latter.
  for (size_t n = 0; n < argv.size(); n++) {
    args[n] = strdup(argv[n].c_str());
  }
  args[argv.size()] = NULL;
}

/*Helper function of 'export_rev', used for updating the environment variable's
value when export.*/
void command_shell::update_env(std::map<std::string, std::string> & vars,
                               std::string & varname,
                               std::vector<std::string> & envv) {
  //construct the line of 'variable=variable value'
  std::string varline = varname;
  varline.append("=");
  varline.append(vars[varname]);

  //check if this variable is already exported as an envrionment variables
  for (size_t i = 0; i < envv.size(); i++) {
    std::string tmpname = "";
    for (size_t j = 0; j < envv[i].length(); j++) {
      if (envv[i][j] != '=') {
        tmpname.push_back(envv[i][j]);
      }
      else {
        break;
      }
    }
    if (tmpname == varname) {
      envv[i] = varline;  //if so, change correspnding value
      return;
    }
  }
  envv.push_back(varline);  //if not, add a new one
}

/*Helper function of 'export_rev', used for command 'rev', revser the value for
correspnding variable using double pointers and swap*/
void command_shell::var_rev(std::map<std::string, std::string> & vars,
                            std::string & varname) {
  size_t i = 0;
  size_t j = vars[varname].size() - 1;
  while (i <= j) {
    std::swap(vars[varname][i], vars[varname][j]);
    i++;
    j--;
  }
}

/*This function is for initialzie the envirionment variables' record envv,
it will run once at the beginning, save the current envrionment variables into
vector envs.*/
void command_shell::init_env(std::vector<std::string> & envv) {
  char * s = *environ;
  int i = 1;
  while (s) {
    std::string tmp(s);
    envv.push_back(tmp);
    s = *(environ + i);
    i++;
  }
}

/*Top Level*/

/*Top level function of this shell. It would run the shell, print directories,
read in command line, manage variables, arguments and call funcions.*/
int command_shell::ffosh() {
  /*initialize part*/

  //var map, used for stroring values of variables
  std::map<std::string, std::string> vars;

  //get PATH
  char * ECE551PATH = getenv("PATH");
  std::string path = ECE551PATH;
  vars["ECE551PATH"] = path;

  //env vector, used for storing envirionment variables and values
  std::vector<std::string> envv;
  init_env(envv);

  /*run the shell in loop, until meet 'exit' or 'EOF'*/
  while (true) {
    //read in current directory and print
    char * cur_dir = get_current_dir_name();
    std::cout << "ffosh:" << cur_dir << " $";

    //read in command line
    std::string command_string;
    std::getline(std::cin, command_string);
    char * command_line = strdup(command_string.c_str());

    //check command line for 'exit' or 'EOF'
    if (!std::cin.good()) {
      free(cur_dir);
      free(command_line);
      break;
    }
    else if (!strcmp(command_line, "exit")) {
      free(cur_dir);
      free(command_line);
      break;
    }

    //no exit/EOF continue running
    else {
      //parse the command line for arguments and save them in vector argv
      std::vector<std::string> argv;
      size_t argc = 0;
      if (parse(command_line, argv, &argc)) {
        std::cerr << "command line format error!" << std::endl;
      }
      else {
        //processing data structures for arguments and envc
        // char** env, for envrionment variables, used for execve
        char ** envs = new char *[envv.size() + 1];
        //number of env variables
        size_t envc = envv.size();
        //map of env, used for checking if env variable is valid
        std::map<std::string, std::string> envm;
        // char** args, for arguments
        char ** args = new char *[argv.size() + 1];
        getenv_arg(envs, args, envv, argv, envm);

        //parse the command line for variables, if any, replace the variable with value
        parsevar(argc, args, vars, envm);

        //build in command cd
        if (!strcmp(args[0], "cd")) {
          if (changedir(argc, args)) {
            std::cerr << "change dir failed." << std::endl;
          }
        }
        //build in command set
        else if (!strcmp(args[0], "set")) {
          if (setvar(command_line, argc, args, vars)) {
            std::cerr << "set var failed" << std::endl;
          }
        }
        //build in command export
        else if (!strcmp(args[0], "export")) {
          if (export_rev<true>(envv, vars, argc, args)) {
            std::cerr << "exprot var failed" << std::endl;
          }
        }
        //build in command rev
        else if (!strcmp(args[0], "rev")) {
          if (export_rev<false>(envv, vars, argc, args)) {
            std::cerr << "rev var failed" << std::endl;
          }
        }
        //other commands
        else {
          // if absolute path is provided, use the path directly
          if (strchr(args[0], '/') == NULL) {
            search_and_exe<true>(argc, args, vars["ECE551PATH"], envs);
          }
          // else, search ECE551PATH and then execute
          else {
            search_and_exe<false>(argc, args, vars["ECE551PATH"], envs);
          }
        }
        freecmd(argc, args);
        freecmd(envc, envs);
      }
      free(command_line);
    }
    free(cur_dir);
  }
  return EXIT_SUCCESS;
}

/*run the shell in main*/
int main(void) {
  command_shell cs;
  cs.ffosh();
  return EXIT_SUCCESS;
}
