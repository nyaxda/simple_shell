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
	char placeholder[MAX_SIZE], **arrstore = malloc(MAX_SIZE * sizeof(char *));
	int i = 0, j;

	if(arrstore == NULL)
		return (NULL);
	
	free(prompt);
	prompt = NULL;
	if (cust_getline(&prompt, &extent, stdin) == -1)
	{
		/*check if it's end of file and there is no more input*/
		if (feof(stdin))
		{
			return (NULL);
		}
		else
		{
			perror("getline error");
			return (NULL);
		}
	}
	strncpy(placeholder, cust_strtk(prompt, " \t\n"), MAX_SIZE);
	while (placeholder[0] != '\0')
	{
		arrstore[i] = malloc(MAX_SIZE);
		if (arrstore[i] == NULL)
		{
			for(j = 0; j < i; j++)
				free(arrstore[j]);
			free(arrstore);
			free(prompt);
			return (NULL);
		}
		strncpy(arrstore[i], placeholder, MAX_SIZE);
        strncpy(placeholder, cust_strtk(NULL, " \t\n"), MAX_SIZE);
        i++;
	}
	arrstore[i] = NULL;
	i = 0;
	free(prompt);
	return (arrstore);
}
