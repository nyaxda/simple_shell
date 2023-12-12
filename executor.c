#include "main.h"

int executor(const char **arrstore)
{
	char **directories, *path, *prompt_path, *token;
	int i, status, found = 0;
	pid_t child_process_id;

	directories = malloc(sizeof(char *) * 1024);
	if (directories == NULL)
	{
		perror ("1");
		return (-1);
	}
	path = strdup(getenv("PATH"));
	token = cust_strtk(path, ":");
	for (i = 0; token != NULL; i++)
	{
		directories[i] = strdup(token);
		token = cust_strtk(NULL, ":");
		printf("%s\n", directories[i]);
	}
	directories[i] = NULL;
	prompt_path = malloc(sizeof(char) * 1024);
	for (i = 0; directories[i] != NULL; i++)
	{
		if (arrstore[0][0] == '/')
		{
			snprintf(prompt_path, 1024, "%s", arrstore[0]);
			printf("%s\n", prompt_path);
		}
		else
		{
			snprintf(prompt_path, sizeof(prompt_path), "%s/%s",directories[i], arrstore[0]);
			printf("%s\n", prompt_path);
		}
		if (access(prompt_path, F_OK) == 0)
		{
			printf("%s this is the found path to executable file\n", prompt_path);
			found = 1;
			break;
		}
	}
	
	if (found != 0)
	{
		child_process_id = fork();
		if	(child_process_id == -1)
		{
			perror("Fork Error");
			exit(0);
		}
		else if (child_process_id == 0)
		{
			if(execve(prompt_path, (char * const *)arrstore, NULL) < 0)
			{
				perror("Error: Execution of command failed");
				exit(EXIT_FAILURE);
			}
		}
		else
		wait(&status);
	}
	else
	{
		perror("4");
	}
	for (i = 0; directories[i] != NULL; i++)
		free(directories[i]);
	free(directories);
	free(path);
	free(prompt_path);
	return (status);
}
