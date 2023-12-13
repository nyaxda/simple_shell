#include "main.h"

/**
 * _strchr - locates a character in a string.
 * Description: function that locates a character in a string.
 *
 *@s: pointer to a char
 *@c: char
 *
 * Return: pointer to the first occurrence of the character
 * c in the string s, or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	size_t i = 0;
	size_t len = strlen(s);

	while (i <= len)
	{
		if (s[i] == c)
		{
			return (s + i);
		}
		i++;
	}
	return (NULL);
}

