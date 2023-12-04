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
		printer("($) ");
	}
}
