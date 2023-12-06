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
	pid_t child_process_id = fork();
	char prompt_path[1024], *en_output, buffer[1024], *output, numbuff[100];
	const char *directories[] = {"/bin", "/usr/bin", "/usr/sbin", "/sbin"};

	if (strcmp(arrstore[0], "exit") == 0)
		exit(0);
	/* child process has failed to initiate*/
	if (child_process_id == -1)
	{
		perror("Error");
		exit(1);
	}
	else if (child_process_id == 0)
	{
		if (strcmp(arrstore[0], "env") == 0)
		{
			buf_size = sizeof(buffer);
			en_output = _getenviron(NULL);
			snfprinter(buffer, buf_size, "%s\n", en_output);
			output = strdup(buffer);
			printer(output);
			free(en_output);
			free(output);
		}
		/*child process occurs here*/
		if (arrstore[0][0] == '/')
    	{
        	/* If the command starts with '/', assume it's an absolute path */
        	snprintf(prompt_path, sizeof(prompt_path), "%s", arrstore[0]);
        	if (execve(prompt_path, (char * const *)arrstore, NULL) == -1)
			{
				perror("Error");
				free(arrstore);
				arrstore = NULL;
				exit(0);
			}
    	}
    	else
		{
			for(i = 0; i < sizeof(directories)/sizeof(directories[0]); i++)
			{
				/*looking for filename PATH*/
				snfprinter(prompt_path, sizeof(prompt_path), "%s/",
				directories[i]);
				snfprinter(prompt_path + strlen(prompt_path),
				sizeof(prompt_path)- strlen(prompt_path), "%s", arrstore[0]);
				if (execve(prompt_path, (char * const *)arrstore, NULL) != -1)
				{
					break;
				}
			}
		}
		if (i == sizeof(directories)/sizeof(directories[0]))
		{
			perror("Error");
			/*free arrstore memory and exit the child process*/
			free(arrstore);
			exit(0);
		}
	}
	else
		wait(&status);	/*snfprinter(prompt_path, sizeof(prompt_path), "/bin/%s", arrstore[0]);*/
	if (strcmp(arrstore[0], "echo") == 0)
	{
    	for (j = 1; arrstore[j] != NULL; j++)
    	{
        	if (strcmp(arrstore[j], "$?") == 0)
        	{
            	print_integer(WEXITSTATUS(status), numbuff);
        		arrstore[j] = numbuff;
				execve("/bin/echo", (char * const *)arrstore, NULL);
    			return;
        	}
    	}
	}
}
