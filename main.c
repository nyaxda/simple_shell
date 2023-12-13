#include "main.h"

void handle_command(char **arrstore, char *prompt)
{
    if (strcmp(arrstore[0], "setenv") == 0)
    {
        if(arrstore[1] != NULL && arrstore[2] != NULL)
            cust_setenv(arrstore[1],arrstore[2]);
        else
            handle_error("Insufficient setenv arguments", prompt, arrstore);
    }
    else if (strcmp(arrstore[0], "unsetenv") == 0)
    {
        if (arrstore[1] != NULL)
            cust_unsetenv(arrstore[1]);
        else
            handle_error("Insufficient unsetenv arguments", prompt, arrstore);
    }
    else if (strcmp(arrstore[0], "cd") == 0)
    {
        cust_cd(arrstore[1]);
    }
    else
        executor((const char **)arrstore);
}

void handle_error(char *message, char *prompt, char **arrstore)
{
    perror(message);
    free(prompt);
    free(arrstore);
    exit (1);
}

int main(void)
{
    int size = 1024;
    char **arrstore = malloc(sizeof(char) * size);
    char *prompt = malloc(sizeof(char) * size), **new_arrstore;

    if (arrstore == NULL || prompt == NULL)
        return (0);

    while (1)
    {
        prompter();
        new_arrstore = input_text(prompt, size);
        if (new_arrstore == NULL)
        {
            handle_input_error(prompt, arrstore);
            continue;
        }
        free(arrstore);
        arrstore = new_arrstore;
        if (arrstore[0] != NULL)
            handle_command(arrstore, prompt);
        free(arrstore);
        arrstore = NULL;
    }
    free(prompt);
    return (0);
}

void handle_input_error(char *prompt, char **arrstore)
{
    if (isatty(STDIN_FILENO))
        return;
    free(prompt);
    if (arrstore != NULL)
        free(arrstore);
    exit(0);
}