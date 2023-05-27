#include "shell.h"

/**
 * my_exit - exits the shell
 * @shell_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if shell_info.argv[0] != "exit"
 */
int my_exit(shell_info_t *shell_info) {
	int exit_status;

	if (shell_info->argv[1] != NULL) { /* If there is an exit arguement */
		exit_status = _erratoi(shell_info->argv[1]);
		if (exit_status == -1) {
			shell_info->status = 2;
			print_error(shell_info, "Illegal number: ");
			_eputs(shell_info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		return (exit_status);
	}
	return (0);
}

/**
 * my_cd - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_cd(shell_info_t *shell_info) {
	char *current_directory, *new_directory, *old_directory;
	int chdir_return;

	current_directory = getcwd(NULL, 1024);
	if (current_directory == NULL) {
		_puts("TODO: >>getcwd failure emsg here<<\n");
		return (-1);
	}
	if (shell_info->argv[1] == NULL) {
		new_directory = getenv("HOME");
		if (new_directory == NULL) {
			new_directory = "/";
		}
	} else {
		new_directory = shell_info->argv[1];
	}
	old_directory = getenv("OLDPWD");
	chdir_return = chdir(new_directory);
	if (chdir_return == -1) {
		print_error(shell_info, "can't cd to ");
		_eputs(new_directory);
		_eputchar('\n');
	} else {
		setenv("OLDPWD", old_directory, 1);
		setenv("PWD", new_directory, 1);
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @shell_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_help(shell_info_t *shell_info) {
	_puts("help call works. Function not yet implemented \n");
	return (0);
}
