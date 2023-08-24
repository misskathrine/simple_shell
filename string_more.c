#include "shell.h"
/**
 * _strcpy - FUNC copies a string from source to destination
 *
 * @source: the string source
 *
 * @dest: the string destination
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *source)
{
	int a;

	for (a = 0; source[a] != '\0'; a++)
	{
		dest[a] = source[a];
	}
	dest[a] = '\0';
	return (dest);
}
/**
 * _isalpha - check if the input is a letter
 *
 * @c: the character to be checked
 *
 * Return: 1 if letter, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (SUCCESS);
	}
	return (FAIL);
}

