#include "main.h"

/**
 * cust_setenv - custome sentenv that implements sentenv into our cusom shell
 *
 * @name: environment variable name.
 * @value: value to be assigned.
 * @overwrite: Flag indicator. 1 to overwrite and 0 not to overwrite.
 * Return: 0 on success, -1 on failure.
 */
int cust_setenv(const char *name, const char *value, int overwrite)
{
	char *envvalue;

	if (name == NULL || name[0] == '\0')
	{
		perror("Name not found");
		exit(1);
	}
	if (overwrite != 0 && overwrite != 1)
	{
		perror("Invalid overwrite value");
		exit(1);
	}
	if (overwrite == 1)
	{
		envvalue = getenv(name);
		if(envvalue == NULL)
		{
			perror("Environment variable non-existent");
			return(-1);
		}
		if (setenv(name, value, overwrite) == -1)
		{
			perror("Failed to set new Env Variable");
			return (-1);
		}
		return (0);
	}
	return (0);
}

/**
 * cust_unsetenv - Unsets an environment variable.
 *
 * @name: The name of the environment variable to unset.
 * Return: 0 on success, -1 on failure.
 */
int cust_unsetenv(const char *name)
{
	if (name == NULL || name[0] == '\0')
	{
		perror("Name not found");
		exit(1);
	}
	if (unsetenv(name) == -1)
	{
		perror("Failed to set Unset Env Var");
		return (-1);
	}
	return (0);
}
