#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * read_line - Reads a line from stdin
 *
 * Return: The line from stdin
 */

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	char *prompt_text = malloc(100 * sizeof(char));

	strcpy(prompt_text, "$ ");
	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(prompt_text);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror(prompt_text);
			free(prompt_text);
			exit(EXIT_FAILURE);
		}
	}

	free(prompt_text);

	return (line);
}
