#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ;


/**
 * read_line - Reads a line from stdin
 *
 * Return: The line from stdin
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
 * split_line - Splits a line into an array of tokens
 * @line: The line
 *
 * Return: Null-terminated array of tokens
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
 * launch_program - Splits a line into an array of tokens
 * @args: Launch and manages the processes
 *
 * Return: Null-terminated array of tokens
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
 * execute_command - Executes a command
 * @args: Null-terminated array of arguments
 *
 * Return: 1 if the shell should continue running, 0 otherwise
 */

int execute_command(char **args)
{
	if (args[0] == NULL)
	{
		return (1);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)
		{
			write(STDOUT_FILENO, *env, strlen(*env));
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}

		return (1);
	}

	return (launch_program(args));
}

/**
 * main - Entry point of the shell program
 *
 * Return: 0 if successful, 1 if an error occurs
 */

int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		args = split_line(line);
		status = execute_command(args);

		free(line);
		free(args);
	} while (status);

	return (EXIT_SUCCESS);
}
