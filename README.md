# minishell

### Mandatory part
- You must program a mini UNIX command interpreter.
- This interpreter must display a prompt (a simple "$> " for example) and wait till
you type a command line, validated by pressing enter.
- The prompt is shown again only once the command has been completely executed.
- The command lines are simple, no pipes, no redirections or any other advanced
functions.
- The executable are those you can find in the paths indicated in the PATH variable.
- In cases where the executable cannot be found, it has to show an error message and
display the prompt again.
- You must manage the errors without using errno, by displaying a message adapted
to the error output.
- You must deal correctly with the PATH and the environment (copy of system char
**environ).
- You must implement a series of builtins: echo, cd, setenv, unsetenv, env, exit.
- You can choose as a reference whatever shell you prefer.
- You must manage expansions $ and ˜

### Bonus part
Quite a few features will be on the menu of the 21sh and 42sh projects. Below are some
bonuses that you can start implementing immediately. Only if you wish to do so!
- Management of signals and in particular Ctrl-C. The use of global variables is
allowed as part of this bonus.
- Management of execution rights in the PATH.
- Auto completion.
- The separation of commands with ";".
- Other bonuses that you will think to be useful.

## General Instructions
- The executable file must be named minishell.
- You must submit a Makefile. That Makefile needs to compile the project and
must contain the usual rules. It can only recompile the program if necessary.
- If you are clever, you will use your library for your minishell. Also submit your
folder libft including its own Makefile at the root of your repository. Your
Makefile will have to compile the library, and then compile your project.
- Your project must be written in C in accordance with the Norm.
- You have to handle errors in a sensitive manner. In no way can your program quit
in an unexpected manner (Segmentation fault, bus error, double free, etc).
- Your program cannot have memory leaks.
- Within your mandatory part you are allowed to use the following functions:
  - malloc, free
  - access
  - open, close, read, write
  - opendir, readdir, closedir
  - getcwd, chdir
  - stat, lstat, fstat
  - fork, execve
  - wait, waitpid, wait3, wait4
  - signal, kill
  - exit
- You are allowed to use other functions to carry out the bonus part as long as their
use is justified during your defence. For example, to use tcgetattr is justified in
certain case, to use printf because you are lazy isn’t. Be smart!
