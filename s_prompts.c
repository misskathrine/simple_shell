#include "shell.h"

/**
 * myprompt - Print shell prompt to standard input.
 *
 * Return: void.
 */
void myprompt(void)
{
	puts(PROMPT);
	fflush(stdout);
}
