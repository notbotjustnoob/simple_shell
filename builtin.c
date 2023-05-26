#include "shell.h"

/**
 * my_exit - exits the shell
 * @shell_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if shell_info.argv[0] != "exit"
 */
int my_exit(shell_info_t *shell_info)
{
	int exitcheck;

	if (shell_info->argv[1] != NULL) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(shell_info->argv[1]);
		if (exitcheck == -1)
		{
			shell_info->status = 2;
			print_error(shell_info, "Illegal number: ");
			_eputs(shell_info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		shell_info->err_num = _erratoi(shell_info->argv[1]);
		return (-2);
	}
	shell_info->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_cd(shell_info_t *shell_info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (shell_info->argv[1] == NULL)
	{
		dir = _getenv(shell_info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(shell_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(shell_info->argv[1], "-") == 0)
	{
		if (!_getenv(shell_info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(shell_info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(shell_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell_info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(shell_info, "can't cd to ");
		_eputs(shell_info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(shell_info, "OLDPWD", _getenv(shell_info, "PWD="));
		_setenv(shell_info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

