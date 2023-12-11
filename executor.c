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
	size_t i, j, buf_size,k;
	pid_t child_process_id;
	char prompt_path[1024], *en_output, buffer[1024], *output, numbuff[100],
	*exit_code[3] = {"echo", NULL, NULL}, *directories[1024] = {NULL}, *token, *msg, *path;

	msg = malloc(200 * sizeof(char));
	path = strdup(getenv("PATH"));
	token = cust_strtk(path, ":");
	k = 0;
	while (token != NULL)
	{
		directories[k] = token;
		token = cust_strtk(NULL, ":");
		k++;
	}
	directories[k] = NULL;

	if (strcmp(arrstore[0], "exit") == 0)
	{
		if (arrstore[1] != NULL)
		{
			exitstus = atoi(arrstore[1]);
			exit(exitstus);
		}
		else
			exit(0);
	}
	printf("step 2\n");
	if (arrstore[0][0] == '/')
    {
        /* If the command starts with '/', assume it's an absolute path */
        snfprinter(prompt_path, sizeof(prompt_path), "%s", arrstore[0]);
		if (access(prompt_path, F_OK) == 0)
			child_process_id = fork();
		else
		{
			snfprinter(msg, sizeof(msg), "sh: %s: not found\n", prompt_path);
			printer(msg);
			/*freed((char **)arrstore);*/
			/*charfree(msg);*/
			exit(1);
		}
		printf("step 3\n");
    }
	else
	{
		for(i = 0; directories[i] != NULL; i++)
		{
			printf("Start of else\n");
			snfprinter(prompt_path, sizeof(prompt_path), "%s/", directories[i]);
			printf("%s\n", prompt_path);
			snfprinter(prompt_path + strlen(prompt_path), sizeof(prompt_path)
			- strlen(prompt_path), "%s", arrstore[0]);
			printf("%s\n", prompt_path);
	        if (access(prompt_path, F_OK) == 0)
			{
        	    child_process_id = fork();
				printf("child process\n");
			}
			else
				continue;
		}
		if (directories[i] == NULL)
    	{
        	snfprinter(msg, sizeof(msg), "sh: %s: not found\n", arrstore[0]);
       		printer(msg);
			printf("Step where directory list is exhausted and no exec file found\n");
        	/*freed((char **)arrstore);*/
        	exit(1);
    	}
	}
	printf("step 4\n");
	/* child process has failed to initiate*/
	if (child_process_id == -1)
	{
		perror("Error");
		printf("No child process step\n");
		exit(EXIT_FAILURE);
	}
	
	else if (child_process_id == 0)
	{
		printf("Is a child\n");
		if (strcmp(arrstore[0], "echo") == 0)
		{
    		for (j = 1; arrstore[j] != NULL; j++)
    		{
        		if (strcmp(arrstore[j], "$?") == 0)
        		{
            		print_integer(WEXITSTATUS(status), numbuff);
					exit_code[1] = numbuff;
					execve("/bin/echo", (char * const *)exit_code, NULL);
					printf("exit code handled\n");
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
			printf("env handled\n");
		}
		else
		if (execve(prompt_path, (char * const *)arrstore, NULL) == -1)
		{
			snfprinter(msg, sizeof(msg), "sh: %s: not found\n", arrstore[0]);
			printer(msg);
			printf("execve failed\n");
			/*freed((char **)arrstore);*/
			/*charfree(msg);*/
			exit(1);
		}

		charfree(en_output);
		charfree(output);
		/*_exit(0);*/
		/*child process occurs here*/
		printf("step 6\n");
	}
	else
		wait(&status);
	if (WIFEXITED(status))
			exitstus = WEXITSTATUS(status);
	if (msg != NULL)
	{
		charfree(msg);
		msg = NULL;
	}
	printf("step done\n");
}
