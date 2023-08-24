#include "shell.h"

/**
 * error_f - This frees alloc'd pointers following system error
 * @argv: pointer to a pointer to an array of pointers
 * @arg: pointer to a pointer to an array of chars
 *
 * Return: void.
 */
void error_f(char **argv, char *arg)
{
	int k;

	for (k = 0; argv[k]; k++)
		free(argv[k]);
	free(argv);
	free(arg);
	exit(EXIT_FAILURE);
}

/**
 * tokens_f - func to free memory allocated dynamically by tokenize()
 * @ptr: pointer to allocated memory
 *
 * Return: void.
 */
void tokens_f(char **ptr)
{
	int k;

	for (k = 0; ptr[k]; k++)
		free((ptr[k]));
	free(ptr);
}


/**
 * paths_f - func to Free the global variable containing the PATH environment
 *              variable value
 *
 * Return: Nothing
 */
void paths_f(void)
{
	if (environ != NULL)
	{
		size_t k = 0;

		while (environ[k] != NULL)
		{
			if (strncmp(environ[k], "PATH=", 5) == 0)
			{
				free(environ[k]);
				environ[k] = NULL;
				break;
			}
			k++;
		}
	}
}
