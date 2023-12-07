#include "main.h"

/**
 * cutter - Trims leading and trailing whitespace charactes.
 * @untrimmed: The input string to be trimmed.
 * Return: The trimmed string.
 */
char *cutter(char *untrimmed)
{
	char *duplicate, *cut;

	duplicate = untrimmed;
	if (duplicate == NULL || *duplicate == '\0')
		return (duplicate);
	while (isspace(*duplicate))
		duplicate++;
	cut = duplicate + strlen(duplicate) - 1;
	while(cut > duplicate && isspace(*cut))
		cut--;
	*(cut + 1) = '\0';
	return (duplicate);
}

/**
 * command_separator - Separates a command line and executes.
 *
 * Description: Separates command line into individual commands, ';'
 * being the delimiter. Each command is then processed by the
 * cutter, parser, and executor functions.
 *
 * @command_line: The command line to be processed.
 * Return: void;
 */
void command_separator(char *command_line)
{
	char *buffer, **carray, **ag;
	int i = 0;
	size_t j, size;

	buffer = cust_strtk(command_line, ";");
	carray = malloc(sizeof(char *) * 1024);
	while(buffer)
	{
		carray[i] = buffer;
		buffer = cust_strtk(NULL, ";");
		i++;
	}
	carray[i] = NULL;
	size = i;

	for (j = 0; j < size; j++)
	{
		carray[j] = cutter(carray[j]);
		ag = parser(carray[j]);
		executor((const char **)ag);
		free(ag);
	}
	free(carray);
}

/**
 * parser - Parses a string into an array of command  arguments.
 *
 * @carray: The string to be parsed.
 * Return: NULL if memory allocation fails, string array if successful.
 */
char **parser(char *carray)
{
	int i = 0;
	char **cmargmnts = malloc (sizeof(char *) * 1024), *buffer;
	if (cmargmnts == NULL)
		return (NULL);

	buffer = cust_strtk(carray, " ");
	while(buffer)
	{
		cmargmnts[i] = buffer;
		buffer = cust_strtk(NULL, " ");
		i++;
	}
	cmargmnts[i] = NULL;
	return (cmargmnts);
}
