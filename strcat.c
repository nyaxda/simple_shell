#include "main.h"

/**
 * str_concat - concatenates two strings.
 *
 * Description: function that concatenates two strings.
 *
 *@s1: pointer to a string.
 *@s2: pointer to a string.
 *
 * Return: NULL if str = NULL. On success,
 * returned pointer should point to a newly
 * allocated space in memory which contains
 * the contents of s1, followed by the contents of s2,
 * and null terminated.
 */
char *str_concat(char *s1, char *s2)
{
	char *m;
	size_t i, len_s1, len_s2;

	if (s1 == NULL)
	{
		s1 = "";
	}
	if (s2 == NULL)
	{
		s2 = "";
	}

	len_s1 = strlen(s1);
	len_s2 = strlen(s2);

	m = malloc(len_s1 * sizeof(char) + len_s2 * sizeof(char) + 1);

	if (m == NULL)
	{
		return (NULL);
	}
	else
	{
		for (i = 0; i < len_s1; i++)
		{
			m[i] = s1[i];
		}

		while (i < (len_s1 + len_s2))
		{
			m[i] = s2[i - len_s1];
			i++;
		}
		m[i] = '\0'; // Ensure the string is null-terminated
	}
	return (m);
}
