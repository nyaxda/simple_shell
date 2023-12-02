#include "main.h"

/**
 * printer - Prints the given message to the standard output.
 *
 * This function writes the provided message to the standard output file descriptor.
 * @msg: The message to be printed.
 * Return: void.
 */
void printer(const char *msg)
{
	write(STDOUT_FILENO, msg, strlen(msg));
}

/**
 * snprinter - Prints the given message to the standard output.
 * @str: The buffer to store the message.
 * @extent: The maximum number of characters to print.
 * @format: The format of the message.
 * Return: void.
*/
void snprinter(char *str, size_t extent, const char *format, ...)
{
	va_list args;
	char buffer[1024] = "", *argstring; // Assuming a maximum buffer size of 1024

	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
			{
				argstring = va_arg(args, char*);
				if (strlen(buffer) + strlen(argstring) >= extent)
				{
					perror("snprinter: buffer overflow.\n");
					exit(1);
				}
				strcat(buffer, argstring);
			}
		}
		else
		{
			if (strlen(buffer) + 1 >= extent)
			{
				perror("snprinter: buffer overflow");
				exit(1);
			}
			char ch[2] = {*format, '\0'};
			strcat(buffer, ch);
		}
		format++;
	}
	va_end(args);
	strncpy(str, buffer, extent);
}
