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
<<<<<<< HEAD
void executor(const **char arrstore);
=======
void executor(char *const arrstore);
>>>>>>> d29b64f74390f385b36b3fe777f221e0fb1f228b

#endif /*MAIN_H_*/
