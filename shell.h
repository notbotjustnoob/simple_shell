#ifndef SHELL_H
#define SHELL_H


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ;

char **split_line(char *line);
char *read_line(void);
int execute_command(char **args);
int launch_program(char **args);
void handle_sigint(int sig);
void check_for_path(char **args);

#endif /* SHELL_H */
