#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * main - Entry point of the shell program
 *
 * Return: 0 if successful, 1 if an error occurs
 */

int main(void)
{
	int state = 1;
	char *line;
	char **args;
	int interactive = isatty(STDIN_FILENO);
	char *prompt_text = malloc(100 * sizeof(char));

	strcpy(prompt_text, "$ ");
	do {
		if (interactive)
		{
			write(1, prompt_text, strlen(prompt_text));
			fflush(stdout);
			}
		line = read_line();
		args = split_line(line);
		if (strcmp(args[0], "exit") != 0 && strcmp(args[0], "\0") != 0)
		{
			execute(args);
			free(line);
			free(args);
			}
		else
		{
			if (strcmp(args[0], "exit") == 0)
			{
				state = 0;
				free(line);
				free(args);
			}
		}

	} while (state == 1);
	free(line);
	free(args);
	free(prompt_text);
	return (1);
}
