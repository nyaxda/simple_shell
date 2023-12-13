#include "main.h"

/**
 * handle_command - Executes the appropriate action based on the command provided.
 *
 * @arrstore: An array of strings containing the command and its arguments.
 * @prompt: The prompt string displayed to the user.
 * Return: void.
 */
void handle_command(char **arrstore, char *prompt)
{
	if (strcmp(arrstore[0], "setenv") == 0)
	{
		if(arrstore[1] != NULL && arrstore[2] != NULL)
			cust_setenv(arrstore[1],arrstore[2]);
		else
			handle_error("Insufficient setenv arguments", prompt, arrstore);
	}
	else if (strcmp(arrstore[0], "unsetenv") == 0)
	{
		if (arrstore[1] != NULL)
			cust_unsetenv(arrstore[1]);
		else
			handle_error("Insufficient unsetenv arguments", prompt, arrstore);
	}
	else if (strcmp(arrstore[0], "cd") == 0)
	{
		cust_cd(arrstore[1]);
	}
	else
		executor((const char **)arrstore);
}

/**
 * handle_error - Handles an error by printing an error message
 * and freeing allocated memory, and exiting the program.
 *
 * @message: The error message to be printed.
 * @prompt: The prompt string to be freed.
 * @arrstore: The array of strings to be freed.
 * Return: void.
 */
void handle_error(char *message, char *prompt, char **arrstore)
{
	perror(message);
	free(prompt);
	free(arrstore);
	exit (1);
}

/**
 * main - This file contains the main function of the simple_shell program.
 *
 * @return 0 on successful execution.
 */
int main(void)
{
	int size = 1024;
	char **arrstore = malloc(sizeof(char) * size);
	char *prompt = malloc(sizeof(char) * size), **new_arrstore;

	if (arrstore == NULL || prompt == NULL)
		return (0);

	while (1)
	{
		prompter();
		new_arrstore = input_text(prompt, size);
		if (new_arrstore == NULL)
		{
			handle_input_error(prompt, arrstore);
			continue;
		}
		free(arrstore);
		arrstore = new_arrstore;
		if (arrstore[0] != NULL)
			handle_command(arrstore, prompt);
		free(arrstore);
		arrstore = NULL;
	}
	free(prompt);
	return (0);
}

/**
 * handle_input_error - Handles input error by freeing allocated
 * memory and exiting the program.
 *
 * @prompt: The prompt message to be freed.
 * @arrstore: The array of strings to be freed.
 * Return: void.
 */
void handle_input_error(char *prompt, char **arrstore)
{
	if (isatty(STDIN_FILENO))
		return;
	free(prompt);
	if (arrstore != NULL)
		free(arrstore);
	exit(0);
}