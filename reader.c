#include "main.h"

/**
 * input_text - Reads input from the user and stores it
 * in the provided buffer.
 *
 * Description: it handles the end of file condition,
 * and also removes new line.
 * @prompt: The buffer to store the user input.
 * @extent: The maximum number of characters to read.
 *
 * Return: void
 */
char **input_text(char *prompt, size_t extent)
{
	char *placeholder, **arrstore = NULL;
	int i = 0;

	free(prompt);
	prompt = NULL;
	if (cust_getline(&prompt, &extent, stdin) == -1)
	{
		/*check if it's end of file and there is no more input*/
		if (feof(stdin))
		{
			free(arrstore);
			return (NULL);
		}
		else
		{
			perror("getline error");
			free(arrstore);
			return (NULL);
		}
	}
	placeholder = cust_strtk(prompt, " \t\n");
	arrstore = malloc(sizeof(char *) * 1024);
	if (arrstore == NULL)
	{
		free(prompt);
		return (NULL);
	}

	while (placeholder)
	{
		arrstore[i] = placeholder;
		placeholder = cust_strtk(NULL, " \t\n");
		i++;
	}
	arrstore[i] = NULL;
	i = 0;
	free(prompt);
	return (arrstore);
}
