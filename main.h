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
void snprinter(char *str, size_t extent, const char *format, ...);
void executor(const **char arrstore);

#endif /*MAIN_H_*/
