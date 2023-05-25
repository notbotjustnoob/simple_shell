#include "shell.h"

/**
 * check_for_path - Check if a command exists within the PATH
 * @args: Null-terminated array of strings representing command-line arguments
 */

void check_for_path(char **args)
{
	if (args[0][0] != '/')
	{
		char *path_env = strdup(getenv("PATH"));
		char *path = strtok(path_env, ":");
		char *full_path = malloc(strlen(path) + strlen(args[0]) + 2);

		while (path != NULL)
		{
			strcpy(full_path, path);
			strcat(full_path, "/");
			strcat(full_path, args[0]);

			if (access(full_path, X_OK) == 0)
			{
				args[0] = full_path;
				break;
			}
			path = strtok(NULL, ":");
		}
		free(path_env);
	}
}

/**
 * execute_command - Execute commands
 * @args: Command-line arguments
 * Return: 0 if command is "exit", otherwise 1
 */

int execute_command(char **args)
{
	if (args[0] == NULL)
	{
		return (1);
	}

	check_for_path(args);

	if (strcmp(args[0], "exit") == 0)
	{
		return (0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		char **env;

		for (env = environ; *env; ++env)
			write(STDOUT_FILENO, *env, strlen(*env));

		return (1);
	}
	else
	{
		return (launch_program(args));
	}
}
