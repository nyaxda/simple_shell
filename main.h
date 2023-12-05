#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>

void prompter(void);
void printer(const char *msg);
char **input_text(char *prompt, size_t extent);
void snfprinter(char *print, size_t size, const char *format,
const char *insert);
void executor(const char **arrstore);
char *_getenviron(const char *current);
char *str_concat(char *s1, char *s2);
char *_strchr(char *s, char c);

#endif /*MAIN_H_*/
