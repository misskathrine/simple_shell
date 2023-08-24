#include "shell.h"
/**
 * is_path_form - Helps check if the given file is a PATH
 *
 * @myshell: A pointer to data struct
 *
 * Return: 1 if success or 0 if otherwise
 */
int is_path_form(sh_t *myshell)
{
	if (_strchr(myshell->args[0], '/') != 0)
	{
		myshell->cmd = _strdup(myshell->args[0]);
		return (SUCCESS);
	}
	return (FAIL);
}
#define DELIMITER ":"
/**
 * is_short_form - Help determine if given filename is short form
 *
 * @myshell: A pointer to data struct
 *
 * Return: 1 if success or 0 if otherwise
 */
void is_short_form(sh_t *myshell)
{
	char *path, *token, *_path;
	struct stat st;
	int exist_flag = 0;

	path = _getenv("PATH");
	_path = _strdup(path);
	token = strtok(_path, DELIMITER);
	while (token)
	{
		myshell->cmd = _strcat(token, myshell->args[0]);
		if (stat(myshell->cmd, &st) == 0)
		{
			exist_flag += 1;
			break;
		}
		free(myshell->cmd);
		token = strtok(NULL, DELIMITER);
	}
	if (exist_flag == 0)
	{
		myshell->cmd = _strdup(myshell->args[0]);
	}
	free(_path);
}
#undef DELIMITER
/**
 * is_builtin - checks if the command is builtin
 *
 * @myshell: A pointer to the data struct
 *
 * Return: success on execution
 */
int is_builtin(sh_t *myshell)
{
	blt_t blt[] = {
		{"exit", terminate_program},
		{"cd", directory_chg},
		{"help", help_display},
		{NULL, NULL}
	};
	int a = 0;

	while ((blt + a)->cmd)
	{
		if (_strcmp(myshell->args[0], (blt + a)->cmd) == 0)
			return (SUCCESS);
		a++;
	}
	return (NEUTRAL);
}

