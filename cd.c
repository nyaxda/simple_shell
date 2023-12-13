#include "main.h"
/**
 * cust_cd - Changes directory according to path
 * @path: The path to the directory to change to.
 * Return: 0 on success, -1 on failure.
 */
int cust_cd(char *path)
{
	static char *switcher;
	char *temp = getcwd(NULL, 0);

	if (path == NULL || strcmp(path, "~") == 0)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			perror("Unable to change path");
			return (-1);
		}
	}
	else if (strcmp(path, "-") == 0)
	{
		if (switcher != NULL)
			path = switcher;
		else
		{
			free(temp);
			perror("Error");
			return (-1);
		}
	}
	if (chdir(path) != 0)
	{
		free(temp);
		perror("Error");
		return (-1);
	}
	free(switcher);
	switcher = temp;
	return (0);
}
