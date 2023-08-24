#ifndef SHELL_H
#define SHELL_H


#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include <unistd.h>


extern char **environ;


#define BUFSIZE 256
#define TOKENSIZE 64
#define PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define PROMPT "$ "
#define SUCCESS (1)
#define FAIL (-1)
#define NEUTRAL (0)

/* Struct */

/**
 * struct sh_shell - Data structure for global shell
 * @line: the input line
 * @args: arguments token
 * @error_msg: for the global path
 * @cmd: the parsed command line
 * @index:  command index
 * @oldpwd: old path
 * @env: the environnment
 *
 * Description: contains all the variables needed to manage
 * the program, memory and accessability
 */
typedef struct sh_shell
{
	char *line;
	char **args;
	char *cmd;
	char *error_msg;
	char *oldpwd;
	unsigned long int index;
	char *env;
} sh_t;

/**
 * struct builtin - function handles and manage builtins
 * @cmd: the command line
 * @f:  associated functions
 *
 * Description: this is the struct for builtin command line
 */
typedef struct builtin
{
	char *cmd;
	int (*f)(sh_t *myshell);
} blt_t;

int read_line(sh_t *);
int split_line(sh_t *);
int parse_line(sh_t *);
int process_cmd(sh_t *);

void shell_exit(char **args);

void myprompt(void);

char *path_g(void);

void sigint_h(int sig);
void sigquit_h(int sig);
void sigstp_h(int sig);

int terminate_program(sh_t *myshell);
int directory_chg(sh_t *myshell);
int help_display(sh_t *myshell);
int builtin_handler(sh_t *myshell);
int check_builtin(sh_t *myshell);

int shell_setenv(char **args);
int shell_unsetenv(char **args);

char *get_input(void);
void input_f(void);

void *get_L(void);
void shell_exit(char **args);

char *_strdup(char *str);
char *_strcat(char *myfirst, char *mysecond);
int _strlen(char *str);
char *_strchr(char *str, char c);
int _strcmp(char *s1, char *s2);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memset(char *s, char byt, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
int free_data(sh_t *);

char *_itoa(unsigned int n);
int intlen(int num);
int _atoi(char *c);
int print_error(sh_t *);
int write_history(sh_t *myshell);
int _isalpha(int c);

char *_strcpy(char *dest, char *source);

void *fill_an_array(void *a, int el, unsigned int len);
void signal_handler(int signo);
char *_getenv(char *path_name);
void index_cmd(sh_t *myshell);
void array_rev(char *arr, int len);


void error_f(char **argv, char *arg);
void tokens_f(char **ptr);
void paths_f(void);

int is_path_form(sh_t *myshell);
void is_short_form(sh_t *myshell);
int is_builtin(sh_t *myshell);

#endif /* SHELL_H */
