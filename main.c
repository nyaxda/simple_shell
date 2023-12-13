#include "main.h"

/**
 * main - entry point of the program
 * Return: 0 (success)
*/
int main(void)
{
	int size = 1024, i, status = 0;
	char *prompt = malloc(sizeof(char) * 1024), **arrstore, *prompt_path;

	if (prompt == NULL)
	{
		perror("Error: Memory allocation to prompt failed");
		return (1);
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
			if (command_handler(arrstore, status) == 0)
			{
				prompt_path = parser(arrstore);
				if (prompt_path != NULL)
				{
					status = executor((const char **)arrstore, prompt_path);
					free(prompt_path);
				}
			}
				status = 0;
				free(arrstore);
		}
		for (i = 0; arrstore[i] != NULL; i++)
			free(arrstore[i]);
		free(arrstore);
		arrstore = NULL;
	}
	free(prompt);
	return (0);
}
