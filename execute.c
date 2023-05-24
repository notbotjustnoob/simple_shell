#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * execute - Executes a command
 * @args: Null-terminated array of arguments
 *
 * Return: 1 if the shell should continue running, 0 otherwise
 */

int execute(char **args)
{
	pid_t pid;
	char *prompt_text = "#cisfun$ ";

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror(prompt_text);
			}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror(prompt_text);
		}
	else
	{
		/*Parent process*/
		wait(NULL);
		}

	return (1);
}
