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
void input_text(char *prompt, size_t extent)
{
	if (fgets(prompt, extent, stdin) == NULL)
	{
		if (feof(stdin))
		{
			printer("End of input reached.\n");
			exit(0);
		}
		else
		{
			perror("fgets");
			exit(1);
		}
	}
	/*Replacing new line with null termination*/
	prompt[strcspn(prompt,"\n")] = '\0';
}
