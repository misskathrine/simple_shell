#include "shell.h"

/**
 * main - Execute command for the shell program.
 *
 * Return: Return: 0 (success) and ----- (Fail)
 */
int main(void)
{
	sh_t shell;
	int pl;

	_memset((void *)&shell, 0, sizeof(shell));
	signal(SIGINT, signal_handler);
	while (1)
	{
		index_cmd(&shell);
		if (read_line(&shell) < 0)
		{
			if (isatty(STDIN_FILENO))
				PRINT("\n");
			break;
		}
		if (split_line(&shell) < 0)
		{
			free_data(&shell);
			continue;
		}
		pl = parse_line(&shell);
		if (pl == 0)
		{
			free_data(&shell);
			continue;
		}
		if (pl < 0)
		{
			print_error(&shell);
			continue;
		}
		if (process_cmd(&shell) < 0)
		{
			print_error(&shell);
			break;
		}
		free_data(&shell);
	}
	free_data(&shell);
	exit(EXIT_SUCCESS);
}

/**
 * read_line - Function that reads a line from the standard input
 * @shell: A pointer to the struct of data
 *
 * Return: Return: 0 (success) and ----- (Fail)
 */
int read_line(sh_t *shell)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, new_size;

	shell->line = malloc(size * sizeof(char));
	if (shell->line == NULL)
		return (FAIL);
	if (isatty(STDIN_FILENO))
		PRINT(PROMPT);
	for (csr_ptr = shell->line, end_ptr = shell->line + size;;)
	{
		read_st = read(STDIN_FILENO, &c, 1);
		if (read_st == 0)
			return (FAIL);
		*csr_ptr++ = c;
		if (c == '\n')
		{
			*csr_ptr = '\0';
			return (SUCCESS);
		}
		if (csr_ptr + 2 >= end_ptr)
		{
			new_size = size * 2;
			length = csr_ptr - shell->line;
			shell->line = _realloc(shell->line, size * sizeof(char),
						new_size * sizeof(char));
			if (shell->line == NULL)
				return (FAIL);
			size = new_size;
			end_ptr = shell->line + size;
			csr_ptr = shell->line + length;
		}
	}
}
#define DELIMITER " \n\t\r\a\v"
/**
 * split_line - splits line to tokens
 * @shell: a pointer to the struct of data
 *
 * Return: Return: 0 (success) and ----- (Fail)
 */
int split_line(sh_t *shell)
{
	char *token;
	size_t size = TOKENSIZE, new_size, i = 0;

	if (_strcmp(shell->line, "\n") == 0)
		return (FAIL);
	shell->args = malloc(size * sizeof(char *));
	if (shell->args == NULL)
		return (FAIL);
	token = strtok(shell->line, DELIMITER);
	if (token == NULL)
		return (FAIL);
	while (token)
	{
		shell->args[i++] =  token;
		if (i + 2 >= size)
		{
			new_size = size * 2;
			shell->args = _realloc(shell->args, size * sizeof(char *),
					new_size * sizeof(char *));
			if (shell->args == NULL)
				return (FAIL);
			size = new_size;
		}
		token = strtok(NULL, DELIMITER);
	}
	shell->args[i] = NULL;
	return (0);
}
#undef DELIMITER
#define DELIMITER ":"
/**
 * parse_line - Function that parses arguments to a valid command
 * @shell: A pointer to the struct of data
 *
 * Return: Return: 0 (success) and ----- (Fail)
 */
int parse_line(sh_t *shell)
{
	if (is_path_form(shell) > 0)
		return (SUCCESS);
	if (is_builtin(shell) > 0)
	{
		if (builtin_handler(shell) < 0)
			return (FAIL);
		return (NEUTRAL);
	}
	is_short_form(shell);
	return (SUCCESS);
}
#undef DELIMITER
/**
 * process_cmd - Function that process commands and execute process
 * @shell: a pointer to the struct of data
 *
 * Return: Return: 0 (success) and ----- (Fail)
 */
int process_cmd(sh_t *shell)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(shell->cmd, shell->args, environ) < 0)
		shell->error_msg = _strdup("not found\n");
			return (FAIL);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (0);
}
