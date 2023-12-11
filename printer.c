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
#include <string.h>

void snfprinter(char *print, size_t size, char *format, ...)
{
    va_list args;
	char *insert, *g;
    char *s = print;
	size_t len;

	va_start(args, format);
	g = format;
    while (*g != '\0' && (size_t)(s - print) < size)
    {
        if (*g == '%' && *(g + 1) == 's')
        {
            insert = va_arg(args, char*);
            len = strlen(insert);

            if ((s - print) + len < size)
            {
                memcpy(s, insert, len);
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

    va_end(args);
}

/**
 * print_integer - print an integer to a buffer
 * @h: integer to print
 * @s: buffer to store the resulting string
 * Return: void.
 */
void print_integer(int h, char *s)
{
    int i = 0, temp = h, size = 0;
    int is_negative = h < 0 ? 1 : 0, extra_space = (h < 0) ? 1 : 0;

    while (temp != 0)
    {
        temp /= 10;
        size++;
    }
    if (is_negative)
        h = -h;
    else if (h == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return;
    }
    i = size + extra_space;
    s[i] = '\0';
    while (size > 0)
    {
        s[--i] = h % 10 + '0';
        h /= 10;
        size--;
    }
    if (is_negative)
        s[--i] = '-';
}