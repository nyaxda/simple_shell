#include "main.h"
/**
 * execute_command - Executes a command based on the input array of strings.
 * Description: utilizes "setenv", "unsetenv", "cd" functions based on the input.
 * Otherwise, it executes the command using the executor function.
 * 
 * @arrstore: The array of strings representing the command and its arguments.
 * Return: void.
 */
void execute_command(char **arrstore)
{
    if (strcmp(arrstore[0], "setenv") == 0)
    {
        if(arrstore[1] != NULL && arrstore[2] != NULL)
            cust_setenv(arrstore[1],arrstore[2]);
        else
        {
            perror("Insufficient setenv arguments");
            exit (1);
        }
    }
    else if (strcmp(arrstore[0], "unsetenv") == 0)
    {
        if (arrstore[1] != NULL)
            cust_unsetenv(arrstore[1]);
        else
        {
            perror("Insufficient unsetenv arguments");
            exit (1);
        }
    }
    else if (strcmp(arrstore[0], "cd") == 0)
    {
        cust_cd(arrstore[1]);
    }
    else
        executor((const char **)arrstore);
}
