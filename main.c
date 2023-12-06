#include "main.h"

/**
 * main - entry point of the program
 * Return: 0 (success)
*/
int main(void)
{
	int size = 1024;
	char **arrstore = malloc(sizeof(char) * 1024);
	char *prompt = malloc(sizeof(char) * 1024);

	if (arrstore == NULL || prompt == NULL)
	{
		return (0);
	}
	while (1)
	{
		prompter();
		arrstore = input_text(prompt, size);
		if (arrstore == NULL)
		{
			free(prompt);
			return (0);
		}
		/*checking if the command is not empty*/
		if (arrstore[0] != NULL)
		{
			executor((const char **)arrstore);
			if (strcmp(arrstore[0], "sentenv") == 0)
			{
				if(arrstore[1] != NULL && arrstore[2] != NULL)
					cust_setenv(arrstore[1],arrstore[2]);
				else
				{
					perror("Insufficient setenv arguments");
					exit (1);
				}
			}
			if (strcmp(arrstore[0], "unsetenv") == 0)
			{
				if (arrstore[1] != NULL)
        			cust_unsetenv(arrstore[1]);
				else
				{
					perror("Insufficient unsetenv arguments");
					exit (1);
				}
			}
		}
		free(arrstore);
	}
	free(prompt);
	return (0);
}
