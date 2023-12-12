#include "main.h"

void executor(const char **arrstore)
{
	char **directories, *buffer, *env_output, *numbuff, *path, prompt_path[1024],
	*token;
	int i, j, status;
	pid_t child_process_id;

	directories = malloc(sizeof(char *) * 1024);
	if (directories == NULL)
	{
		perror ("Error");
		return;
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
	if (strcmp(arrstore[0], "exit") == 0)
		exit(0);
	else if (strcmp(arrstore[0], "echo") == 0)
	{
		for (j = 1; arrstore[j] != NULL; j++)
    	{
        	if (strcmp(arrstore[j], "$?") == 0)
        	{
				numbuff = malloc(sizeof(char *) * 100);
        		print_integer(WEXITSTATUS(status), numbuff);
				free(numbuff);
				break;
    		}
		}
		printer(numbuff);
	}
	else if (strcmp(arrstore[0], "env") == 0)
	{
		env_output = _getenviron(NULL);
		buffer = malloc(sizeof(char) * 1024);
		if (buffer == NULL)
		{
			perror("Error: Mem allocation failed");
			exit(1);
		}
		snprintf(buffer, 1024, "%s\n", env_output);
		printer(buffer);
		free(buffer);
	}
	for (i = 0; directories[i] != NULL; i++)
	{
		if (arrstore[0][0] == '/')
		{
			snprintf(prompt_path, sizeof(prompt_path), "%s", arrstore[0]);
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
			child_process_id = fork();
			break;
		}
		else
		{
			perror("Error: Command not found");
			exit(1);
		}
	}
	if (child_process_id == -1)
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
	for (i = 0; directories[i] != NULL; i++)
		free(directories[i]);
	free(directories);
	free(path);
}
