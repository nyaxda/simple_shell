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

/**
 * snfprinter - custom snfprintf
 *
 * @print: The buffer to store the resulting string.
 * @size: The size of the str buffer.
 * @format: The format string containing "%s" placeholders.
 * @insert: The string to be inserted.
 */

void snfprinter(char *print, size_t size, const char *format,
const char *insert)
{
	const char *g = format;
	char *s = print;
	size_t len = strlen(insert);

	while (*g != '\0' && (s - print) < size)
	{
		if (*g == '%' && *(g + 1) == 's')
		{
			if ((s - print) + len < size)
			{
				strcpy(s, insert);
				s += len;
			}
			g += 2;
		}
		else
		{
			*s++ = *g++;
		}
	}
	*s = '\0';
}
