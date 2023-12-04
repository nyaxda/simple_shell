#include "main.h"

/**
 * executor -executes a command by forking a child process
 * and using execve to run the command.
 * @arrstore: The array of command arguments to be executed.
 * Return: void
 */
void executor(const char **arrstore)
{
	int status
	size_t i;
	pid_t child_process_id = fork();
	char prompt_path[1024];
	const char *directories[] = {"/bin", "/usr/bin", "/usr/sbin", "/sbin"};

	if (strcmp(arrstore[0], "exit") == 0)
	{
		exit(0);
	}
	/* child process has failed to initiate*/
	if (child_process_id == -1)
	{
		perror("Error");
		exit(1);
	}
	else if (child_process_id == 0)
	{
		/*child process occurs here*/
		for(i = 0; i < sizeof(directories)/sizeof(directories[0]); i++)
		{
			/*looking for filename PATH*/
			snfprinter(prompt_path, "%s/%s", directories[i], arrstone[0])
			if (execve(prompt_path, (char * const *)arrstore, NULL) != -1)
			{
				break;
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
		wait(&status);
	/*snfprinter(prompt_path, sizeof(prompt_path), "/bin/%s", arrstore[0]);*/
}
