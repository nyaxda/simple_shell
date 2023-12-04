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
	pid_t child_process_id = fork();
	char prompt_path[1024];

	if (strcmp(arrstore[0], "exit") == 0)
	{
		exit(0);
	}
	if (child_process_id == -1) /* child process has failed to initiate*/
	{
		perror("Error");
		exit(1);
	}
	else if (child_process_id == 0)
	{
		/*child process occurs here*/
		if (execve(arrstore[0], (char * const *)arrstore, NULL) == -1)
		{
			perror("Error");
			/*free arrstore memory and exit the child process*/
			free(arrstore);
			exit(0);
		}
	}
	else
		wait(&status);
	snfprinter(prompt_path, sizeof(prompt_path), "/bin/%s", arrstore[0]);
}
