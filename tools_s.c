#include "shell.h"
/**
 * _getenv - FUNC gets the path
 *
 * @path_name: pointer to data struct
 *
 * Return: success on execution
 */
char *_getenv(char *path_name)
{
	char **environ_cursor, *env_ptr, *name_ptr;

	environ_cursor = environ;
	while (*environ_cursor)
	{
		env_ptr = *environ_cursor;
		name_ptr = path_name;
		while (*env_ptr == *name_ptr)
		{
			if (*env_ptr == '=')
				break;
			env_ptr++;
			name_ptr++;
		}
		if ((*env_ptr == '=') && (*name_ptr == '\0'))
			return (env_ptr + 1);
		environ_cursor++;
	}
	return (NULL);
}
/**
 * signal_handler - function handle the process INTERRUPT signal
 *
 * @signo: the signal identifier
 *
 * Return: void on execution
 */
void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		PRINT("\n");
		PRINT(PROMPT);
	}
}
/**
 * fill_an_array - fill an array with elements
 *
 * @a: the given for execution
 *
 * @el: the given element
 *
 * @len: the length of the array
 *
 * Return: pointer to the array after execution
 */
void *fill_an_array(void *a, int el, unsigned int len)
{
	char *p = a;
	unsigned int i = 0;

	while (i < len)
	{
		*p = el;
		p++;
		i++;
	}
	return (a);
}

/**
 * array_rev - func to reverse array
 *
 * @arr: the given array
 *
 * @len: the array length
 *
 * Return: void on execution
 */
void array_rev(char *arr, int len)
{
	int a;
	char tmp;

	for (a = 0; a < (len / 2); a++)
	{
		tmp = arr[a];
		arr[a] = arr[(len - 1) - a];
		arr[(len - 1) - a] = tmp;
	}
}
/**
 * index_cmd - This determine indexed command
 *
 * @myshell: a pointer to the data structure
 *
 * Return: void on execution
 */
void index_cmd(sh_t *myshell)
{
	myshell->index += 1;
}

