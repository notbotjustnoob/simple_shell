#include "shell.h"

/**
 * read_line - Read a line from stdin
 * Return: A string containing the line read from stdin
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("$");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
/**
 * split_line - Split a line into words
 * @line: The line to split
 * Return: An array of strings, each representing a word in the line
 */
char **split_line(char *line)
{
	int bufsize = BUFFER_SIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "$: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "$: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIMITERS);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * launch_program - Launch and manage child process
 * @args: Null-terminated array of strings representing command-line arguments
 * Return: Always returns 1
 */

int launch_program(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("$");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("$");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}

/**
 * handle_sigint - Handle the SIGINT signal (Ctrl+C input)
 * @sig: Signal number
 */

void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
