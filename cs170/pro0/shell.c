#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_TOKEN_LENGTH 50
#define MAX_TOKEN_COUNT 100
#define MAX_LINE_LENGTH 512

// Simple implementation for Shell command
// Assume all arguments are seperated by space
// Erros are ignored when executing fgets(), fork(), and waitpid(). 

/**
 * Sample session
 *  shell: echo hello
 *   hello
 *   shell: ls
 *   Makefile  simple  simple_shell.c
 *   shell: exit
**/

typedef struct _cmd {
	char* cmd;
	char* args[MAX_TOKEN_COUNT];
	int fdin;
	int fdout;
} Command;


void runcommand(Command cmd) {
  pid_t pid = fork();
  if(pid) { // parent
    	waitpid(pid, NULL, 0);
	if (cmd.fdin) close(cmd.fdin);
	if (cmd.fdout != 1) close(cmd.fdout);
  } else { // child
	if (cmd.fdin) 
		dup2(cmd.fdin, 0);
	if (cmd.fdout != 1) 
		dup2(cmd.fdout, 1);
    	execvp(cmd.cmd, cmd.args);
  }
}

int main(){
    char line[MAX_LINE_LENGTH];
    //printf("shell: "); 
    while(fgets(line, MAX_LINE_LENGTH, stdin)) {
    	// Build the command and arguments, using execv conventions.
    	line[strlen(line)-1] = '\0'; // get rid of the new line
    	Command commands[3];
	int command_count = 0;
	int i;
	for (i = 0; i < 3; i++) 
		commands[i].cmd = NULL;
    	int argument_count = 0;
	commands[command_count].fdout = 1;
	commands[command_count].fdin = 0;
    	char* token = strtok(line, " ");
    	while(token) {
		if (strcmp(token,"|") == 0) {
			int fd[2];
                        if (pipe(fd)) exit(1);

			commands[command_count].args[argument_count] = NULL;
			if (commands[command_count].fdout == 1)
				commands[command_count].fdout = fd[1];
			else
				close(fd[1]);
			command_count++;
			commands[command_count].fdin = fd[0];
			commands[command_count].fdout = 1;
			argument_count = 0;
		} else if (strcmp(token, "<") == 0) {
			int fd = open(strtok(NULL, " "), O_RDONLY);
			if (fd < 0) {
				printf("Cannot find file\n");
				commands[0].cmd = NULL;
				break;
			}
			commands[command_count].fdin = fd;
		} else if (strcmp(token, ">") == 0) {
			int fd = open(strtok(NULL, " "),
				 O_WRONLY|O_TRUNC|O_CREAT, 0644);
			commands[command_count].fdout = fd;
		} else {
      			if(!commands[command_count].cmd)
				commands[command_count].cmd = token;
      			commands[command_count].args[argument_count] = token;
	      		argument_count++;
		}
		token = strtok(NULL, " ");
    	}
    	commands[command_count].args[argument_count] = NULL;
	i = 0;
	while (i < 3 && commands[i].cmd){
		if (strcmp(commands[0].cmd, "exit") == 0)
            		exit(0);
    		runcommand(commands[i]);
		++i;
	}
        //printf("shell: "); 
    }
    return 0;
}
