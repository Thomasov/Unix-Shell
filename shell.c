#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define FALSE 0
#define TRUE 1
int main()
{
	char input[256];
	pid_t pid;
	int status;
	while (1) {
		memset(input, '\0', sizeof(input));
		//display prompt
		write(STDOUT_FILENO, "$ ", 2);
		if (fgets(input, sizeof(input), stdin) == NULL) {
			break;
		}

		int isRedirect = FALSE;
		char *redirectLocation;
		int redirectFile;
		int stdout_copy;

	    //split string
		char *token = strtok(input, " \r\n");
		char *args[32];
		int i = 0;
		while (token != NULL) {
			if (strcmp(token, ">") == 0) {
				isRedirect = TRUE;
				redirectLocation = strtok(NULL, " \r\n");
				break;
			}
			args[i++] = token;
			token = strtok(NULL, " \r\n");
		}
		args[i] = NULL;
	    //end split string

	    //exit command
		if (args[0] && strcmp(args[0], "exit") == 0) {
			break;
		}
	    //fork the processes
	    pid = fork();
		if (pid == 0) { 
			if (isRedirect) {
				stdout_copy = dup(STDOUT_FILENO);
				close(STDOUT_FILENO);
				redirectFile = open(redirectLocation, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
			}
		    //replace the forked process with the command and pass it the arguments
			execvp(args[0], args);
	        //only hit if execvp fails
			perror("execvp");
		}
		else {
			wait (&status);
		}
	}
	return 0;
}