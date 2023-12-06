#include "main.h"

/**
 * display_prompt - function checks if the program is connected to a terminal
 * using isatty and if so writes the shell prompt "$"
 * Return: void
 */

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
	}
}

/**
 * handle_signal - a signal handler function
 * signo: parameter for SIGINT signal(Ctrl+C)
 * Return: the prompt
 */

void handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		display_prompt();
	}
}
