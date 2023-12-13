#include "main.h"

/**
 * main - entry point of the program
 * Return: 0 (success)
*/
int main(void)
{
	int i, status = 0;
	char prompt[MAX_SIZE], *arrstore[MAX_SIZE], prompt_path[MAX_SIZE], **input;
	
	while (1)
	{
		prompter();
		input = input_text(prompt, MAX_SIZE);
		if (input == NULL)
		{
			return (0);
		}
		/*checking if the command is not empty*/
		if (input[0] != NULL)
        {
            for (i = 0; i < MAX_SIZE && input[i] != NULL; i++)
            {
                arrstore[i] = input[i];
            }
			arrstore[i] = NULL;
			if (command_handler(arrstore, status) == 0)
			{
				strncpy(prompt_path, parser(arrstore), MAX_SIZE);
				if (prompt_path[0] != '\0')
				{
					status = executor((const char **)arrstore, prompt_path);
				}
			}
				status = 0;
		}
		for (i = 0; arrstore[i] != NULL; i++)
			arrstore[i][0] = '\0';
		for (i = 0; input[i] != NULL; i++)
            free(input[i]);
        free(input);
	}
	return (0);
}
