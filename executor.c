#inlcude "main.h"

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

void handle_execve(const char **arrstore, const char *directories[])
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
        for(i = 0; i < sizeof(directories)/sizeof(directories[0]); i++)
        {
            snfprinter(prompt_path, sizeof(prompt_path), "%s/", directories[i]);
            snfprinter(prompt_path + strlen(prompt_path), sizeof(prompt_path)- strlen(prompt_path), "%s", arrstore[0]);
            if (execve(prompt_path, (char * const *)arrstore, environ) != -1)
            {
                break;
            }
        }
    }
    if (i == sizeof(directories)/sizeof(directories[0]))
    {
        perror("Error");
        free(arrstore);
        exit(1);
    }
}

void executor(const char **arrstore)
{
    int status, exitstus;
    pid_t child_process_id = fork();
    const char *directories[] = {"/bin", "/usr/bin", "/usr/sbin", "/sbin"};

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
        handle_execve(arrstore, directories);
    }
    else
        wait(&status);

    if (WIFEXITED(status))
    {
        exitstus = WEXITSTATUS(status);
        exit(exitstus);
    }
}