#include "main.h"

/**
 * main - entry point of the program
 * Return: 0 (success)
*/
int main(void)
{
	int size = 1024;
	char **arrstore = malloc(sizeof(char) * size);
	char *prompt = malloc(sizeof(char) * size), **new_arrstore;

	if (arrstore == NULL || prompt == NULL)
	{
		return (0);
	}
	while (1)
	{
		prompter();
		new_arrstore = input_text(prompt, size);
		if (new_arrstore == NULL)
		{
			free(prompt);
			if (arrstore != NULL)
				free(arrstore);
			return (0);
		}
		if (arrstore != NULL)
			free(arrstore);
		arrstore = new_arrstore;
		/*checking if the command is not empty*/
		if (arrstore[0] != NULL)
		{
			if (strcmp(arrstore[0], "setenv") == 0)
			{
				if(arrstore[1] != NULL && arrstore[2] != NULL)
					cust_setenv(arrstore[1],arrstore[2]);
				else
				{
					perror("Insufficient setenv arguments");
					free(prompt);
					free(arrstore);
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
					free(prompt);
					free(arrstore);
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
		free(arrstore);
		arrstore = NULL;
	}
	free(prompt);
	return (0);
}