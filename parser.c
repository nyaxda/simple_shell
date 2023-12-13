#include "main.h"

char *parser(char **arrstore)
{
    char *path, *token = NULL, *prompt_path = NULL, *path_dup;
    int found = 0;

    if (*arrstore == NULL || arrstore == NULL)
    {
        return (NULL);
    }
	path = getenv("PATH");
	if (path == NULL)
	{
		perror("Error: path not found");
		return (NULL);
	}
    path_dup = strdup(path);
    if (path_dup == NULL)
    {
        perror("strdup");
        return (NULL);
    }
	token = strtok(path_dup, ":");
	while (token != NULL)
	{
        prompt_path = realloc(prompt_path, sizeof(char) * 1024);
        if (prompt_path == NULL)
        {
            perror("Memory reallocation error");
            free(path_dup);
            return (NULL);
        }
		if (arrstore[0][0] == '/')
		{
			snprintf(prompt_path, 1024, "%s", arrstore[0]);
			printf("%s\n", prompt_path);
		}
		else
		{
			snprintf(prompt_path, 1024, "%s/%s", token, arrstore[0]);
			printf("%s\n", prompt_path);
		}
		if (access(prompt_path, X_OK) == 0)
		{
			printf("%s this is the found path to executable file\n", prompt_path);
			found = 1;
			break;
		}
        free(prompt_path);
        prompt_path = NULL;
        token = strtok(NULL, ":");
	}
    free(path_dup);
    if (!found)
    {
        free(prompt_path);
        return (NULL);
    }
    return (prompt_path);
}
