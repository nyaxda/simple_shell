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
	char *placeholder, **arrstore;
	int i = 0;

	if (getline(&prompt, &extent, stdin) == -1)
	{
		perror("getline error");
		return (NULL);
	}
	placeholder = strtok(prompt, "\t\n");
	arrstore = malloc(sizeof (char *) * 1024);
	if (arrstore == NULL)
	{
		return (NULL);
	}

	while (placeholder)
	{
		arrstore[i] = placeholder;
		placeholder = strtok(NULL, "\t\n");
		i++;
	}
	arrstore[i] = NULL;
	i = 0;
	return (arrstore);
}
