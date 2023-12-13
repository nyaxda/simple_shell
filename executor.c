#include "main.h"

int executor(const char **arrstore, char *prompt_path)
{
	int status;
	pid_t child_process_id;
	
	if (prompt_path != NULL)
	{
		child_process_id = fork();
		if	(child_process_id == -1)
		{
			perror("Fork Error");
			status = -1;
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
		{
			if (wait(&status) == -1)
			{
				perror("Wait Error");
				status = -1;
			}
		}
	}
	else
	{
		perror("Error: Cannot find executable");
		status = -1;
	}
	return (status);
}
