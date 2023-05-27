#include "shell.h"

/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(shell_info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int setenv(info_t *info, const char *name, const char *value, int overwrite)
{
	if (info->argc != 3 && info->argc != 4)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (overwrite || !getenv(info, name))
	{
		return (add_node_end(&(info->env), name, value) == NULL);
	}
	return (0);
}

/**
 * unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unsetenv(info_t *info, const char *name)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
	{
		list_t *node = info->env;
		while (node)
		{
			if (starts_with(node->str, name))
			{
				delete_node_at_index(&(info->env), get_node_index(info->env, node));
				break;
			}
			node = node->next;
		}
	}

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
