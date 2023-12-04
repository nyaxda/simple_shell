#include "main.h"

/**
 * _getenviron - prints the current environment
 * @current: the current environment
 * Return: void
*/
char *_getenviron(const char *current)
{
    extern char **environ;
    char *value;
    char *name;
    char *output = NULL, *temp;
    int i = 0;

    while(environ [i])
    {
        name = strtok(environ[i], "=");
        value = strtok(NULL, "=");
        if (current == NULL || (name && strcmp(name,current) == 0))
        {
            if (name)
            {
                output = snfprinter("%s", name)
                if (value)
                {
                    temp = snfprinter("=%s\n", holder);
                }
                else
                {
                    temp = snfprinter("=\n");
                }
                output = str_concat(output, temp);
            }
        }
        i++;
    }
    return (output);
}
