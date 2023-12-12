#include "main.h"

/**
 * executor -executes a command by forking a child process
 * and using execve to run the command.
 * @arrstore: The array of command arguments to be executed.
 * Return: void
 */
void executor(const char **arrstore)
{
	int status;
	size_t i, j, buf_size;
	pid_t child_process_id;
	char prompt_path[1024], *en_output, buffer[1024], *output,
	numbuff[100], **directories, *token, *path, *exit_code[2];

	directories = malloc(sizeof(char*) * 1024);
	if (directories == NULL)
	{
		perror("Error");
		exit(1);
	}
	path = strdup(getenv("PATH"));
	token = cust_strtk(path, ":");
	i = 0;
	while (token != NULL)
	{
    	directories[i] = strdup(token);
    	token = cust_strtk(NULL, ":");
		i++;
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
        		print_integer(WEXITSTATUS(status), numbuff);
				exit_code[1] = numbuff;
				execve("/bin/echo", (char * const *)exit_code, NULL);
    			return;
    		}
    	}
	}
	else if (strcmp(arrstore[0], "env") == 0)
	{
		buf_size = sizeof(buffer);
		en_output = _getenviron(NULL);
		snfprinter(buffer, buf_size, "%s\n", en_output);
		output = strdup(buffer);
		printer(output);
		charfree(en_output);
		charfree(output);
	}
	/*child process occurs here*/
	i = 0;
	while (directories[i] != NULL)
	{
		if (arrstore[0][0] == '/')
    		snprintf(prompt_path, sizeof(prompt_path), "%s", arrstore[0]);
 		else
			snprintf(prompt_path, sizeof(prompt_path), "%s/%s", directories[i], arrstore[0]);
		if (access(prompt_path, F_OK) == 0)
			break;
		else
			prompt_path[0] = '\0';
		i++;
	}
	if (directories[i] == NULL && prompt_path[0] == '\0')
	{
		perror("Error");
		exit(1);
	}
	else
	{
		child_process_id = fork();
		/* child process has failed to initiate*/
		if (child_process_id == -1)
		{
			perror("Error");
			exit(1);
		}
		else if (child_process_id == 0)
		{
			if (execve(prompt_path, (char * const *)arrstore, NULL) == -1)
			{
				perror("Error");
				exit(1);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				exitstus = WEXITSTATUS(status);
		}
	}
	free(directories);
}
