#ifndef MAIN_H_
#define MAIN_H_
#define INCREMENT_BUFFER_FACTOR 2
#define BUFFER 1024

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
void prompter(void);
void printer(const char *msg);
char **input_text(char *prompt, size_t extent);
void snfprinter(char *print, size_t size, const char *format,
const char *insert);
void executor(const char **arrstore);
char *_getenviron(const char *current);
char *str_concat(char *s1, char *s2);
char *_strchr(char *s, char c);
char *cust_strtk(char *string, const char *dlm);
ssize_t cust_getline(char **pointer, size_t *n, FILE *strm);
void *cust_realoc(void *ptr, unsigned int old_size, unsigned int new_size);
void print_integer(int h, char *s);
int cust_unsetenv(const char *name);
int cust_setenv(const char *name, const char *value);
int cust_cd(char *path);
char *concatenate_strings(char *output, char *new_output);
char *process_value(char *value, char *new_output);
char *process_env_var(char *environ_var, const char *current, char *output);
void handle_exit(const char **arrstore);
void handle_echo(const char **arrstore, int status);
void handle_execve(const char **arrstore, const char
*directories[], size_t dir_size);
void handle_command(char **arrstore, char *prompt);
void handle_error(char *message, char *prompt, char **arrstore);
void handle_input_error(char *prompt, char **arrstore);
#endif /*MAIN_H_*/
