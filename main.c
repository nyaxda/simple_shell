#include "main.h"\

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
			return (0);
		}
		else if (arrstore[0] != NULL && strcmp(arrstore[0], "exit") == 0)
		{
			free(arrstore);
			return (0);
		}
		executor((const char **)arrstore);
		free(arrstore);
	}
	free(prompt);
	return (0);
}
