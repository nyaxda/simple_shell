#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void prompter(void);
void printer(const char *msg);
void input_text(char *prompt, size_t extent);
void snprinter(char *str, size_t extent, const char *format, ...);

#endif /*MAIN_H_*/
