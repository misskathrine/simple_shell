#include "shell.h"

#define SETOWD(V) (V = _strdup(_getenv("OLDPWD")))
/**
 * directory_chg - function changes to currnet working directory
 *
 * @myshell: pointer to the shell data structure
 *
 * Return: 0 (success) and -----Fail
 */
int directory_chg(sh_t *myshell)
{
	char *home_dir;

	home_dir = _getenv("HOME");
	if (myshell->args[1] == NULL)
	{
		SETOWD(myshell->oldpwd);
		if (chdir(home_dir) < 0)
			return (FAIL);
		return (SUCCESS);
	}
	if (_strcmp(myshell->args[1], "-") == 0)
	{
		if (myshell->oldpwd == 0)
		{
			SETOWD(myshell->oldpwd);
			if (chdir(home_dir) < 0)
				return (FAIL);
		}
		else
		{
			SETOWD(myshell->oldpwd);
			if (chdir(myshell->oldpwd) < 0)
				return (FAIL);
		}
	}
	else
	{
		SETOWD(myshell->oldpwd);
		if (chdir(myshell->args[1]) < 0)
			return (FAIL);
	}
	return (SUCCESS);
}
#undef GETCWD
/**
 * terminate_program - func exit the program
 *
 * @myshell: pointer to the shell data structure
 *
 * Return: 0 success and -----(Fail)
 */
int terminate_program(sh_t *myshell __attribute__((unused)))
{
	int code, i = 0;

	if (myshell->args[1] == NULL)
	{
		free_data(myshell);
		exit(errno);
	}
	while (myshell->args[1][i])
	{
		if (_isalpha(myshell->args[1][i++]) < 0)
		{
			myshell->error_msg = _strdup("Illegal number\n");
			return (FAIL);
		}
	}
	code = _atoi(myshell->args[1]);
	free_data(myshell);
	exit(code);
}
/**
 * help_display - Function displays the help menu
 * @myshell: a pointer to the shell data structure
 *
 * Return: 0 (success) and -----(Fail)
 */
int help_display(sh_t *myshell)
{
	int fd, fw, rd = 1;
	char c;

	fd = open(myshell->args[1], O_RDONLY);
	if (fd < 0)
	{
		myshell->error_msg = _strdup("no help topics match\n");
		return (FAIL);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		fw = write(STDOUT_FILENO, &c, rd);
		if (fw < 0)
		{
			myshell->error_msg = _strdup("cannot write: permission denied\n");
			return (FAIL);
		}
	}
	PRINT("\n");
	return (SUCCESS);
}
/**
 * builtin_handler - Function that handles current working directory
 *
 * @myshell: a pointer to the shell structure
 *
 * Return: 0 (success) and ----- (Fail)
 */
int builtin_handler(sh_t *myshell)
{
	blt_t blt[] = {
		{"exit", terminate_program},
		{"cd", directory_chg},
		{"help", help_display},
		{NULL, NULL}
	};
	int i = 0;

	while ((blt + i)->cmd)
	{
		if (_strcmp(myshell->args[0], (blt + i)->cmd) == 0)
			return ((blt + i)->f(myshell));
		i++;
	}
	return (FAIL);
}
