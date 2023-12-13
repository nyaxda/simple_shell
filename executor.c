#include "main.h"

/**
 * handle_exit - Handles the "exit" command.
 *
 * @arrstore: The array of strings containing the command and its arguments.
 * Return: void.
 */
void handle_exit(const char **arrstore)
{
	int exitstus;

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
}

/**
 * handle_echo - Handles the "echo" command by printing the arguments to the standard output.
 *
 * @arrstore: The array of arguments for the command.
 * @status: The exit status of the previous command.
 * Return: void.
 */
void handle_echo(const char **arrstore, int status)
{
	size_t j;
	char numbuff[100], *exit_code[3] = {"echo", NULL, NULL};

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
}

/**
 * handle_env - Handles the "env" command by printing the environment variables.
 *
 * @arrstore: The array of strings containing the command and its arguments.
 * Return: void.
 */
void handle_env(const char **arrstore)
{
	size_t buf_size;
	char buffer[1024], *en_output, *output;

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
}

/**
 * handle_execve - Executes a command using the execve system call.
 *
 * @arrstore: The array of command arguments.
 * @directories: The array of directories to search for the command.
 * @dir_size: The size of the directories array.
 * Return: void.
 */
void handle_execve(const char **arrstore, const char *directories[], size_t dir_size)
{
	size_t i;
	char prompt_path[1024];

	if (arrstore[0][0] == '/')
	{
		snprintf(prompt_path, sizeof(prompt_path), "%s", arrstore[0]);
		if (execve(prompt_path, (char * const *)arrstore, environ) == -1)
		{
			perror("Error");
			free(arrstore);
			arrstore = NULL;
			exit(1);
		}
	}
	else if (strcmp(arrstore[0], "env") != 0)
	{
		for(i = 0; i < dir_size; i++)
		{
			snfprinter(prompt_path, sizeof(prompt_path), "%s/", directories[i]);
			snfprinter(prompt_path + strlen(prompt_path), sizeof(prompt_path)- strlen(prompt_path), "%s", arrstore[0]);
			if (execve(prompt_path, (char * const *)arrstore, environ) != -1)
			{
				break;
			}
		}
	}
	if (i == dir_size)
	{
		perror("Error");
		free(arrstore);
		exit(1);
	}
}

/**
 * executor - Executes the given command by forking a child process.
 *
 * @arrstore: The array of command arguments.
 * Return: void.
 */
void executor(const char **arrstore)
{
	int status, exitstus;
	pid_t child_process_id = fork();
	const char *directories[] = {"/bin", "/usr/bin", "/usr/sbin", "/sbin"};
	size_t dir_size = sizeof(directories) / sizeof(directories[0]);

	handle_exit(arrstore);

	if (child_process_id == -1)
	{
		perror("Error");
		exit(1);
	}
	else if (child_process_id == 0)
	{
		handle_echo(arrstore, status);
		handle_env(arrstore);
		handle_execve(arrstore, directories, dir_size);
	}
	else
		wait(&status);

	if (WIFEXITED(status))
	{
		exitstus = WEXITSTATUS(status);
		exit(exitstus);
	}
}
