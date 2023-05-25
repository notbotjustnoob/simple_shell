#include "shell.h"

/**
 * main - Main entry point for the shell
 * Return: 0 on normal exit, otherwise the exit status of the last command
 */

int main(void)
{
	char *line;
	char **args;
	int status;

	signal(SIGINT, handle_sigint);

	do {
		write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		args = split_line(line);
		status = execute_command(args);

		free(line);
		free(args);
	} while (status);

	return (EXIT_SUCCESS);
}
