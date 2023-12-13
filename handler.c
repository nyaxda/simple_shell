#include "main.h"

int command_handler(char **arrstore, int status)
{
    char *numbuff, *buffer, *env_output;
    int j;

    if (strcmp(arrstore[0], "setenv") == 0)
    {
        if(arrstore[1] != NULL && arrstore[2] != NULL)
            cust_setenv(arrstore[1],arrstore[2]);
        else
        {
            perror("Insufficient setenv arguments");
            return (1);
        }
        return (1);
    }
    else if (strcmp(arrstore[0], "unsetenv") == 0)
    {
        if (arrstore[1] != NULL)
            cust_unsetenv(arrstore[1]);
        else
        {
            perror("Insufficient unsetenv arguments");
            return (1);
        }
        return (1);
    }
    else if (strcmp(arrstore[0], "cd") == 0)
    {
        cust_cd(arrstore[1]);
        return (1);
    }
    else if (strcmp(arrstore[0], "exit") == 0)
        exit(0);
    else if (strcmp(arrstore[0], "echo") == 0)
    {
        for (j = 1; arrstore[j] != NULL; j++)
        {
            if (strcmp(arrstore[j], "$?") == 0)
            {
                numbuff = malloc(sizeof(char *) * 100);
                if (numbuff == NULL)
                {
                    perror("Error: Memory allocation failed");
                    return(1);
                }
                sprintf(numbuff, "%d", WEXITSTATUS(status));
                printer(numbuff);
                free(numbuff);
                break;
            }
        }
        return (1);
    }
    else if (strcmp(arrstore[0], "env") == 0)
    {
        env_output = _getenviron(NULL);
        buffer = malloc(sizeof(char) * 1024);
        if (buffer == NULL)
        {
            perror("Error: Memory allocation failed");
            return(1);
        }
        snprintf(buffer, 1024, "%s\n", env_output);
        printer(buffer);
        free(buffer);
        return (1);
    }
    return (0);
}
