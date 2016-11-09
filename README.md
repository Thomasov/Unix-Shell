# Unix-Shell
Basic UNIX shell implemented in C that runs on OS X or Linux machines.
 
Works by reading in a line of input at a time where that line represents a UNIX command available in /bin/. The current process is then forked, and if the fork is successful the new child process is replaced by the command specified in the input by using the `execvp` system call. 

A .txt file can be used as input by making a .txt file containing the commands you wish to run and piping it into the executable. For example, with an executable called a.out and a input file called input.txt, you could type `./a.out < input.txt`
