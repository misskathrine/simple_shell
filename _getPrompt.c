#include "shell.h"

static char *last_input;
/**
 * get_input - Func read the line of input from user.
 *
 * Return: Pointer to a buffer conatining the user's input.
*/
char *get_input(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t n_read;

	do {
		myprompt();

		n_read = getline(&input, &input_size, stdin);

		if (n_read == -1)
		{
			free(input);
			puts("\n");
			return (NULL);
		}

		input[n_read - 1] = '\0';

	} while (input[0] == '\0' || isspace(input[0]));

	last_input = input;
	return (input);
}

/**
 * input_f - Frees the most recent input entered by the user.
 *
 * This function frees the memory allocated for the most recent input string
 */
void input_f(void)
{
	free(last_input);
	last_input = NULL;
}
