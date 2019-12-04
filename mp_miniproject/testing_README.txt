**** README for Command Shell ****

1. Instructions
To run the command shell, use "./cmd". There is another executable file 'test',
which is a self-implemented test program, run "./test xxx xxx xxx", it would print
the number of argumnets(including the command itself), then print the arguments themselves,
or trigger some error according to its first argument.

2. Code Structure
The code for this program is divided into two files, 'commandshell.hpp' and 'commandshell.cpp'.

In 'commandshell.hpp' a class is declared (command_shell) and in the class, memer functios of this
shell are declared. Only two templated functions are implemented in .hpp file.

In 'commandshell.cpp' member function are implemented and a simple main funcion is written to run
the shell.

3. Step 1

(1). Clarifications

This step calls ffosh, which is the top level function, which further calls
search_and_exe, in this function, execute is called and finally the command will
be executed using fork, execve, waitpid. If any error occurs, the error
information will be printed into std::cerr.

(2). Testing

     absolute directory for ls:

     /bin/ls
     output: list of files in current directory

     absolute directory for echo:
     
     /bin/echo
     output: an empty line (since there is no arguments)

     absolute directory for test:

     ./test
     output: 1 (since there is no other arguments but the command, number is 1)

     using part of step2 to test error reporting, argument 'fail' will let test
     trigger a EXIT_FAILURE:

     ./test fail
     output: 2
     	     Program failed with code 1
	     
     using part of step2 to test error reporting, argument 'seg' will let test
     trigger a segfault:

     ./test seg
     output: 2
	     Terminated by signal 11
	     
     Quit command shell:
     
     exit
     output: quit the program

     ctrl+D
     output: quit the program

4. Step 2

(1). Clarification

  In the rules for searching commands:
     
     Typing in a command without any '/' means using relative path, the shell
     will search in the ECE551PATH for this command.

     If there is '/' appear in the command, it means an absolute path, the shell
     will try to directly use the path for command.

  In the rules for parsing the argumnets:
     
     "" is not considered as an argumnet, and will not be recorded in args.
     For example "" "" "" will be considered as no argument, and ""aa"" will
     be considered as only one argumnet 'aa'.
     
     "   " is considered as an argumnet will only spaces.
     
     A quote will match the cloest quote.
     For example, ""aa"" is considered as only one argument 'aa'.
     
     There should always be spaces to separete different arguments.
     For example, "aa"a"aa" is considere as argument 'aaaaa', and aa"aa"aa is
     considered as argumnet 'aaaaaa'.
     
(2). Testing

     relative path for system comamnd:

     ls
     output: the list of files in current directory.
     
     echo xxx xxx
     output: xxx xxx

     a command that dosen't exist:

     xxx
     output: Command xxx not found

     ./xxx
     output: Command ./xxx not found

     absolute path of a command that dosen't exist:
     
     /ls
     output: Command /ls not found

     A command that dosen't exist, with arguments:
     
     ./xxx a b c
     output: Command ./xxx not found

     xxx a b c
     output: Command xxx not found

     command 'ls' with argumnets '1' '2' '3':

     ls 1 2 3
     output: /bin/ls: cannot access '1': No such file or directory
     	     /bin/ls: cannot access '2': No such file or directory
	     /bin/ls: cannot access '3': No such file or directory
	     Program failed with code 2

     command 'echo' with argumnets '1' '2' '3':

     echo 1 2 3
     output: 1 2 3

     command line with extra spaces:

           echo 1    2    3    6
     output: 1 2 3 6

     command line with quotes:

     "echo" "1  " "2   " "3   xx" 4
     output: 1   2    3   xx 4

     command line with uclosed quotes:

     echo """""
     output: quote unclosed!
     	     command line format error!

     command line with empty quotes:

     ./test "" 1 "" 2
     output: 3
     	     1
	     2
     (3 arguments, including the command, 1, 2 are printed)

     escape '\'and '"':

     echo \\slash_here \"quote_here
     output: \slash_here "quote_here

     multiple escape '\' and '"':
     
     echo \\\\ \"\"
     output: \\ ""

     mixed quotes and escapes:

     echo "\"\"" "\\\\"
     output: "" \\

5. Step 3

(1). Clarification

   In the rules for 'cd':
      cd only takes one argument, or the shell will reprot error.
      This argument should be a valid path, the shell will call chdir and
      check it.
      
      cd can handle '..', '.', abusolute path and their combinations.
      Combinations like '...' won't be considered as valid.
   
   In the rules for set/export/rev:
      The set command takes at least one argumnet, which is the name of the
      variable. The first argument of set will be parsed just like any argument
      and checked for illegle characters, then used for variable's name.
      
      For example:
      set "123  1" xxx will cause an error, since there are spaces in
      the varname.
      set "123"aa xxx is correct, the varname will be '123aa' and value is 'xxx'.

      The rest part of the command line will all be considered as the value of
      the variable, the value part starts at the second argument.
      If latter arguments are quoted, the quote mark will also be included in
      var value.

      For example:
      set 123 "123 456" "789" will let variable '123' to have value
      '"123 456" "789"'.
      set 123 will let '123' to have an empty value (equal to "").

      Environmnet variables and normal variables(added by set but not exported)
      will be recorded separately, if $varname is wriiten, the value of both
      normal variables and environment variables could be used to replace it.

      To export/rev a variable, it must be set before. User can't rev an
      environment variable that has never been set before.
      Both export and rev takes one argument (which should be the name of an
      argument) once at a time.
      'rev' will only influence variables that is in the record of 'set', the only
      way to change envrionment variables is to 'export'.
      If one variable was not in envirionment variables before, it would add a new
      one to envrionment variables. If it is in the list, the value for it would
      be updated.

(2). Testing
     change directories:
     
     cd .
     output: stay in current directory

     cd ..
     output: go to the upper level of directory

     cd ../008_read3
     cat README
     output: the shell will go to the directory for 008 and print its README

     cd ./xxx
     output: chdir: No such file or directory
             change dir failed.

     set a variable and then replace its name with its value:
     
     set var1 123
     echo $var1
     output: 123

     set a variable and then rev it:
     
     set var1 xxxxddddd
     echo $var1
     output: xxxxddddd
     rev var1
     echo $var1
     output: dddddxxxx

     set a var with all whitepsace:
     
     set var1
     echo $var1
     output: an empty line

     mixed usage of $varname:
     
     set $var1
     echo $var1+$var2 $var1 var1
     output: 123+$var2  123 var1

     set a var with quote:
     
     set "123"aaa "ghj \"" ll
     echo $123aaa
     output: "ghj \"" ll

     env:

     env
     output: the shell will print all envrionment variables currently

     set   "var1"    "666  777"9    
     export var1
     env var1
     output: the shell will print a list of envirionment variables, with
     	     'var1="666  777"9' in it
     rev var1
     export var1
     env
     output: the shell will print a list of envirionment variables, with
     	     'var1=9"777  666"' in it

          
