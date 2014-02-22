#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>

#include <iostream>

#define PIPE_READ 0
#define PIPE_WRITE 1

using namespace std;

char* stripwhite(char *string);
void execute_command(char *s);
void execute_line_helper(char *command_list[], int command_counts, int command_index);

void execute_line(char *s) {

	/* parse line to array of commands */
	char *command;
	char *command_list[strlen(s) / 2];	// at most strlen(s) / 2 arguments
	int command_counts;
	for (command_counts = 0, command = strtok(s, "|"); command;
		command = strtok(NULL, "|"), command_counts++) {
		command_list[command_counts] = command;
	}
	command_list[command_counts] = NULL;

	/* execute line */
	execute_line_helper(command_list, command_counts, 0);
	
}

void execute_line_helper(char *command_list[], 
						int command_counts, 
						int command_index) {
	// if no commands found
	if (command_counts == 0) return;

	// fork off a child
	pid_t cpid;
	switch (cpid = fork()) {
	case -1:
		// fork error
		perror("fork");
		exit(EXIT_FAILURE);
	
	case 0:
		// child process
		if (command_index == command_counts - 1) {
			// the last/only command
			execute_command(command_list[command_index]);
		} else {
			// pipe communication
			int pipefd[2];

			// more than one command left
			if (pipe(pipefd) == -1) {
				// pipe creation error
				perror("pipe");
				exit(EXIT_FAILURE);
			}

			pid_t gcpid;
			// fork off a grandchild
			switch (gcpid = fork()) {
			case -1:
				// fork error
				perror("fork");
				exit(EXIT_FAILURE);
			
			case 0:
				// grandchild process
				dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
				close(pipefd[PIPE_READ]);
				execute_command(command_list[command_index]);

			default:
				// child process
				dup2(pipefd[PIPE_READ], STDIN_FILENO);
				close(pipefd[PIPE_WRITE]);
				execute_line_helper(command_list, command_counts, command_index + 1);
				int status;
				waitpid(gcpid, &status, 0);
			}
		}

	default:
		// parent process
		int status;
		waitpid(cpid, &status, 0);
	}
}


void execute_command(char *s) {
	/* parse argument */
	char *token;
	// at most strlen(s) / 2 arguments
	char *argv[strlen(s) / 2];
	int argc;
	for (argc = 0, token = strtok(s, " "); token;
		token = strtok(NULL, " "), argc++) {
		argv[argc] = token;
	}
	argv[argc] = NULL;

	/* execute command */
	// automatically search in PATH variable
	execvp(argv[0], argv);
	printf("-550shell: %s: command not found\n", argv[0]);
}

int main(int argc, char **argv) {

	// handle user input loop
	char *line, *s;
	while (true) {

		// print shell prompt "$" and read new line
		line = readline("550shell$$$ ");
		// if EOF and empty line, shell terminates
		if (!line) break;

		// remove leading and trailing whitespace
		s = stripwhite(line);
		if (*s) {
			add_history(line);
			execute_line(s);
		}

		// readline malloc line so must free line
		free(line);
	}
}

// remove leading and trailing whitespace
char* stripwhite(char *string) {
	char *s, *t;
	for (s = string; iswspace(*s); ++s) {}
	for (t = string + strlen(string) - 1; iswspace(*t); --t) {}
	*(++t) = '\0';

	return s;
}

