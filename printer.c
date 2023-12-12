#include "main.h"

/**
 * printer - Prints the given message to the standard output.
 *
 * This function writes the provided message to the
 * standard output file descriptor.
 * @msg: The message to be printed.
 * Return: void.
 */
void printer(const char *msg)
{
	write(STDOUT_FILENO, msg, strlen(msg));
}