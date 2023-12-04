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
	size_t i;

	if (s1 == NULL)
	{
		s1 = "";
	}
	if (s2 == NULL)
	{
		s2 = "";
	}

	m = malloc(strlen(s1) * sizeof(char) + strlen(s2) * sizeof(char) + 1);

	if (m == NULL)
	{
		return (NULL);
	}
	else
	{
		for (i = 0; i < strlen(s1); i++)
		{
			m[i] = s1[i];
		}

		while (i < (strlen(s1) + strlen(s2)))
		{
			m[i] = s2[i - strlen(s1)];
			i++;
		}
	}
	return (m);
}
