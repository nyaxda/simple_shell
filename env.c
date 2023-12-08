#include "main.h"

/**
 * _getenviron - prints the current environment
 * @current: the current environment
 * Return: void
*/
char *_getenviron(const char *current)
{
	extern char **environ;
	char *value, *environ_var, *name, *new_output, *old_output, *eq;
	char *output = NULL, *temp, buffer[1024], temp_buffer[1024], *ooutput;
	int i = 0;
	size_t size, temp_size;

	while(environ [i])
	{
		environ_var = strdup(environ[i]);
		if (!environ_var)
		{
			perror("Error");
			free(output);
			return (NULL);
		}
		eq = _strchr(environ_var, '=');
		if (eq)
		{
			*eq = '\0';
			name = environ_var;
			value = eq + 1;
		}
		else
		{
			name = environ_var;
			value = NULL;
		}

		if (current == NULL || (name && strcmp(name,current) == 0))
		{
			if (name)
			{
				size = sizeof(buffer);
				snfprinter(buffer, size, "%s", name);
				new_output = strdup(buffer);
				if (!new_output)
				{
					perror("Error");
					free(environ_var);
					free(output);
					return (NULL);
				}
				if (value)
				{
					temp_size = sizeof(temp_buffer);
					if(environ[i+1])
						snfprinter(temp_buffer, temp_size, "=%s\n", value);
					else
						snfprinter(temp_buffer, temp_size, "=%s", value);
					temp = strdup(temp_buffer);
					if (!temp)
					{
						perror("Error");
						free(new_output);
						free(environ_var);
						free(output);
						return (NULL);
					}
				}
				else
				{
					temp = strdup("");
					if (!temp)
					{
						perror("Error");
						free(new_output);
						free(environ_var);
						free(output);
						return (NULL);
					}
				}
				ooutput =str_concat(new_output, temp);
				free(new_output);
				new_output = ooutput;
				free(temp);
				if (output != NULL)
				{
					old_output = output;
					output = str_concat(old_output, new_output);
					free(old_output);
				}
				else
				{
					output = strdup(new_output);
				}
				free(new_output);
			}
		}
		free(environ_var);
		i++;
	}
	return (output);
}
