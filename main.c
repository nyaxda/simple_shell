#include "main.h"

/**
 * main - entry point of the program
 * Return: 0 (success)
*/
int main(void)
{
	int i, size = 1024;
	char **arrstore = NULL, **holder = NULL;
	char *prompt;

	while (1)
	{
		prompt = malloc(sizeof(char) * 1024);
		prompter();
		arrstore = input_text(prompt, size);
		if (arrstore == NULL)
		{
			free(prompt);
			return (0);
		}
		if (prompt[0] != '\0')
		{
			command_separator(prompt);
		}
		/*checking if the command is not empty*/
		if (arrstore[0] != NULL)
		{
			if(_strchr(prompt, ';'))
			{
				holder = command_separator(prompt);
				free(arrstore);
				arrstore = holder;
			}
			while (arrstore[i] != NULL)
			{
				execute_command(arrstore[i]);
				i++;
			}
			free(arrstore);
		}
		free(prompt);
		free(holder);
		holder = NULL;
	}
	return (0);
}
