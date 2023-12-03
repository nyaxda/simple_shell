#include "main.h"

void executor(const char **arrstore)
{
	int status;
	pid_t child_process_id = fork();

	if (child_process_id == -1) /* child process has failed to initiate*/
	{
		perror ("Error:");
		exit(1);
	}
	else if (child_process_id == 0)
	{
		/*child process occurs here*/
		if (execve (arrstore[0], arrstore, NULL) == -1)
			perror ("Error:");
	}
	else
		wait(&status);
	snfprinter(prompt_path, sizeof(prompt_path),"/bin/%s", prompt);
}
