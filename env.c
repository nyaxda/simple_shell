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
    char *output = NULL, *temp, buffer[1024], temp_buffer[1024], *ooutput;
    int i = 0;
    size_t size, temp_size;

    while(environ [i])
    {
        name = strtok(environ[i], "=");
        value = strtok(NULL, "=");
        if (current == NULL || (name && strcmp(name,current) == 0))
        {
            if (name)
            {
                size = sizeof(buffer);
                snfprinter(buffer, size, "%s", name);
                output = strdup(buffer);
                if (!output)
                {
                    perror("Error");
                    return (NULL);
                }
                if (value)
                {
                    temp_size = sizeof(temp_buffer);
                    snfprinter(temp_buffer, temp_size, "=%s\n", value);
                    temp = strdup(temp_buffer);
                    if (!temp)
                    {
                        perror("Error");
                        return (NULL);
                    }
                }
                else
                {
                    temp = strdup("=\n");
                    if (!temp)
                    {
                        perror("Error");
                        return (NULL);
                    }
                }
                ooutput =str_concat(output, temp);
                free(output);
                output = ooutput;
                free(temp);
            }
        }
        i++;
    }
    return (output);
}
