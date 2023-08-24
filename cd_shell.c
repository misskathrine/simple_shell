#include "shell.h"

/**
 * cdir_shell - This changes the current working directory of the shell
 * @args: array of args
 */
void cdir_shell(char **args)
{
	char *dir = args[1];
	int ret_val;


	if (dir == NULL)
	{
		dir = _getenv("HOME");
		if (dir == NULL)
		{
			puts("cd: No HOME directory found\n");
			return;
		}
	}

	ret_val = chdir(dir);
	if (ret_val == -1)
	{
		perror("cd");
	}
}
