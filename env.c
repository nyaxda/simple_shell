#include "main.h"

char *concatenate_strings(char *output, char *new_output)
{
    char *old_output;

    if (output != NULL)
    {
        old_output = output;
        output = str_concat(old_output, new_output);
        free(old_output);
    }
    else
    {
        output = strdup(new_output);
    }

    return output;
}

char *process_value(char *value, char *new_output)
{
    char *temp, temp_buffer[1024];
    size_t temp_size;

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
        temp = strdup("");
        if (!temp)
        {
            perror("Error");
            return (NULL);
        }
    }

    new_output = str_concat(new_output, temp);
    free(temp);

    return new_output;
}

char *process_env_var(char *environ_var, const char *current, char *output)
{
    char *value, *name, *new_output, *eq;
    char buffer[1024];
    size_t size;

    eq = _strchr(environ_var, '=');
    if (eq)
    {
        *eq = '\0';
        name = environ_var;
        value = eq + 1;
    }
    else
    {
        name = environ_var;
        value = NULL;
    }

    if (current == NULL || (name && strcmp(name,current) == 0))
    {
        if (name)
        {
            size = sizeof(buffer);
            snfprinter(buffer, size, "%s", name);
            new_output = strdup(buffer);
            if (!new_output)
            {
                perror("Error");
                return (NULL);
            }
            new_output = process_value(value, new_output);
            output = concatenate_strings(output, new_output);
            free(new_output);
        }
    }
    free(environ_var);

    return output;
}

char *_getenviron(const char *current)
{
    extern char **environ;
    char *environ_var;
    char *output = NULL;
    int i = 0;

    while(environ [i])
    {
        environ_var = strdup(environ[i]);
        if (!environ_var)
        {
            perror("Error");
            return (NULL);
        }
        output = process_env_var(environ_var, current, output);
        if (!output)
        {
            return (NULL);
        }
        i++;
    }
    return (output);
}