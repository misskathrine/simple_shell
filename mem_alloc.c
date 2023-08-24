#include "shell.h"

/**
 * _realloc - Function that reallocates memory block
 * @pointer: pointer to the old memory
 * @old_size: the old size
 * @new_size: the new size
 *
 * Return: a pointer to the new memory
 */
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	void *result;

	if (new_size == old_size)
		return (pointer);
	if (new_size == 0 && pointer)
	{
		free(pointer);
		return (NULL);
	}
	result = malloc(new_size);
	if (result == NULL)
		return (NULL);
	if (pointer == NULL)
	{
		fill_an_array(result, '\0', new_size);
		free(pointer);
	}
	else
	{
		_memcpy(result, pointer, old_size);
		free(pointer);
	}
	return (result);
}
/**
 * _memset - Sets the memory with constant byte
 * @s: Pointer to the memory area
 * @n: first n bytes
 * @byt: constant byte
 *
 * Return: A pointer to a string
 */
char *_memset(char *s, char byt, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
	{
		s[a] = byt;
	}
	return (s);
}
/**
 * free_data - function that frees shell data
 *
 * @shell: the data structure
 *
 * Return: Return: 0 (success) and ----- (Fail)
 */
int free_data(sh_t *shell)
{
	free(shell->line);
	shell->line = NULL;
	free(shell->args);
	shell->args = NULL;
	free(shell->cmd);
	shell->cmd = NULL;
	free(shell->error_msg);
	shell->error_msg = NULL;
	return (0);
}
/**
 * _memcpy - function that copies memory area
 *
 * @dest: Memory destination
 *
 * @src: The Source for memory area
 *
 * @n: Number of memory byte
 *
 * Return: A pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
	{
		dest[a] = src[a];
	}
	return (dest);
}
