#include "main.h"

/**
 * executor -executes a command by forking a child process
 * and using execve to run the command.
 * @arrstore: The array of command arguments to be executed.
 * Return: void
 */
void executor(const char **arrstore)
{
	int status, exitstus;
	size_t i, j, buf_size;
	pid_t child_process_id = fork();
	char prompt_path[1024], *en_output, buffer[1024], *output,
	numbuff[100], **directories, *token, *path, *exit_code[2];

	directories = malloc(sizeof(char*) * 1024);
	if (directories == NULL)
	{
		perror("Error");
		exit(1);
	}
	path = getenv("PATH");
	token = cust_strtk(path, ":");
	i = 0;
	while (token != NULL)
	{
    	directories[i] = token;
    	token = cust_strtk(NULL, ":");
		i++;
	}
	directories[i] = NULL;

	if (strcmp(arrstore[0], "exit") == 0)
	{
		if (arrstore[1] != NULL)
		{
			exitstus = atoi(arrstore[1]);
			freed(directories);
			exit(exitstus);
		}
		else
			freed(directories);
			exit(0);
	}
	if (strcmp(arrstore[0], "echo") == 0)
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
	if (strcmp(arrstore[0], "env") == 0)
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
	if (directories[i] == NULL)
	{
		perror("Error");
		exit(1);
	}
	/* child process has failed to initiate*/
	if (child_process_id == -1)
	{
		perror("Error");
		freed(directories);
		exit(1);
	}
	if (child_process_id == 0)
	{
		if (execve(prompt_path, (char * const *)arrstore, NULL) == -1)
		{
			perror("Error");
			freed(directories);
			exit(1);
		}
		else
			freed(directories);
			exit(0);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			exitstus = WEXITSTATUS(status);
	}
	freed(directories);
}
