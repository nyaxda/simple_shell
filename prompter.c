#include "main.h"

/**
 * prompter - displays the prompt symbol ($) to the user.
 * Description: prints the prompt symbol, indicating that the user needs
 * to enter a command in the shell.
 * Return: void.
 */
void prompter(void)
{
	/*checks if a stdin is a terminal*/
	if (isatty(STDIN_FILENO))
	{
		char *buffer = malloc(sizeof(char) * 1000), prompt[1024];
		if (buffer == NULL)
		{
			perror("malloc");
			exit(1);
		}
		if (getcwd(buffer, 1000) != NULL)
		{
			snfprinter(prompt, sizeof(prompt), "($)%s# ", buffer);
			printer(prompt);
			free(buffer);
		}
		else
		{
			free(buffer);
			printer("($) ");
		}
	}
}
