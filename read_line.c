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

char *read_line(char *line)
{
	line = NULL;
	size_t bufsize = 0;
	char *prompt_text = "$ ";
	size_t len;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror(prompt_text);
			exit(EXIT_FAILURE);
		}
	}
    len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        {
			line[len - 1] = '\0';
			}
	free(bufsize);
	free(prompt_text);
	free(len);
	return (line);
}
