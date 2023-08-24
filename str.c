#include "shell.h"

/**
 * _strcat - this concatenates two string in a path form
 * @myfirst: the first given destination
 * @mysecond: the second given source
 *
 * Return: 0 (success) and ----- (Fail)
 */
char *_strcat(char *myfirst, char *mysecond)
{
	int len1, len2, i = 0, j = 0;
	char *result;

	len1 = _strlen(myfirst);
	len2 = _strlen(mysecond);
	result = malloc((len1 + len2 + 2) * sizeof(char));
	if (!result)
		return (NULL);
	*result = '\0';
	while (myfirst[j])
		result[i++] = myfirst[j++];
	result[i++] = '/';
	j = 0;
	while (mysecond[j])
		result[i++] = mysecond[j++];
	result[i] = '\0';
	return (result);
}
/**
 * _strlen - func that finds the length of a character string
 * @str: character string
 *
 * Return: 0 (success) and ----- (Fail)
 */
int _strlen(char *str)
{
	int len;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
/**
 * _strcmp - compare two strings
 * @s1: first string character
 * @s2: second string character
 *
 * Return:  0, or -1.
 */
int _strcmp(char *s1, char *s2)
{
	int s = 0, i;

	if (s1 == NULL || s2 == NULL)
		return (1);
	for (i = 0; s1[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			s = s1[i] - s2[i];
			break;
		}
		else
			continue;
	}
	return (s);
}
/**
 * _strchr - func locates a character in a given string
 * @str:  character in string
 * @c:  given string
 *
 * Return: NULL if fail, otherwise returns (success)
 */
char *_strchr(char *str, char c)
{
	char *pointer;

	if (str == NULL)
		return (NULL);
	for (pointer = str; *pointer; pointer++)
		if (*pointer == c)
			return (pointer);
	return (NULL);
}
/**
 * _strdup - func provides a dynamic dup of by str  allocating memory
 *
 * @str: character in string
 *
 * Return:  a pointer to the duplicated string or (NULL)
 */
char *_strdup(char *str)
{
	char *dupl;

	if (str == NULL)
		return (NULL);
	dupl = malloc(_strlen(str) + 1);
	if (dupl == NULL)
		return (NULL);
	_strcpy(dupl, str);
	return (dupl);
}
