#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * split_line - Splits a line into an array of tokens
 * @line: The line
 *
 * Return: Null-terminated array of tokens
 */

char **split_line(char *line)
{
	char *prompt_text = malloc(100 * sizeof(char));
	char msgerror[50];
	char **args = malloc(2 * sizeof(char *));

	strcpy(prompt_text, "$ ");

	if (!args)
	{
		strcpy(msgerror, prompt_text);
		strcat(msgerror, " allocation error\n");
		write(1, msgerror, strlen(msgerror));
		fflush(stdout);
		exit(EXIT_FAILURE);
		}

	line[strcspn(line, "\n")] = '\0';
	args[0] = line;
	args[1] = NULL;

	free(prompt_text);

	return (args);
}
