#include "main.h"

char *parser(char **arrstore)
{
    char **directories, *path, *token, *prompt_path;
    int i, found = 0;

    directories = malloc(sizeof(char *) * 1024);
	if (directories == NULL)
	{
		perror ("Mamory allocation error");
		return (NULL);
	}
	path = strdup(getenv("PATH"));
	if (path == NULL)
	{
		perror("Error: path not found");
        free(directories);
		return (NULL);
	}
	token = cust_strtk(path, ":");
	for (i = 0; token != NULL; i++)
	{
		directories[i] = strdup(token);
        if (directories[i] == NULL)
        {
            perror("Memory allocation error");
            free(path);
            for (i = 0; directories[i] != NULL; i++)
                free(directories[i]);
            free(directories);
            return (NULL);
        }
		token = cust_strtk(NULL, ":");
	}
	directories[i] = NULL;

	prompt_path = malloc(sizeof(char) * 1024);
    if (prompt_path == NULL)
    {
        perror("Memory allocation error");
        free(path);
        for (i = 0; directories[i] != NULL; i++)
            free(directories[i]);
        free(directories);
        return (NULL);
    }
	for (i = 0; directories[i] != NULL; i++)
	{
		if (arrstore[0][0] == '/')
		{
			snprintf(prompt_path, 1024, "%s", arrstore[0]);
			printf("%s\n", prompt_path);
		}
		else
		{
			snprintf(prompt_path, 1024, "%s/%s",directories[i], arrstore[0]);
			printf("%s\n", prompt_path);
		}
		if (access(prompt_path, F_OK) == 0)
		{
			printf("%s this is the found path to executable file\n", prompt_path);
			found = 1;
			break;
		}
	}
    free(path);
    for (i = 0; directories[i] != NULL; i++)
        free(directories[i]);
    free(directories);
    if(found)
        return (prompt_path);
    else
    {
        free(prompt_path);
        return (NULL);
    }
}
