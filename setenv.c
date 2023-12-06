/**
 * cust_setenv - custome sentenv that implements sentenv into our cusom shell
 * 
 * @name: environment variable name.
 * @value: value to be assigned.
 * @overwrite: Flag indicator. 1 to overwrite and 0 not to overwrite.
 * Return: 0 on success, -1 on failure.
 */
int cust_setenv(const char *name, const char *value, int overwrite)
{
    char *envvalue, envname;
    char *envar = malloc (strlen(name) + strlen(value) + 2);
    size_t i;

    i = strlen(name) + strlen(value) + 2;
    if (name == NULL || name[0] == '\0')
    {
        perror("Name not found");
        exit(1);
    }
    if (value != 0 || value != 1)
    {
        perror("Invalid overwrite value");
        exit(1);
    }
    if (value == 0)
        exit (0);
    if (value == 1)
    {
        envvalue = getenv(name);
        snfprinter(envar, strlen(name) + 1, "%s", name);
        strcat(envar, "=");
        snfprinter(envar + strlen(name), strlen(value) + 1, "%s", value);
        if (setenv(name, envar,1) == -1)
        {
            free(envar);
            perror("Failed to set new Env Variable");
            return (-1);
        }
        free(envar);
        return (0);
    }
}

/**
 * char_unsetenv - Unsets an environment variable.
 * 
 * @name: The name of the environment variable to unset.
 * Return: 0 on success, -1 on failure.
 */
int char_unsetenv(const char *name)
{
    if (name == NULL || name[0] == '\0')
    {
        perror("Name not found");
        exit(1);
    }
    if (unsetenv(name) == -1)
    {
        perror("Failed to set Unset Env Var");
        return (-1);
    }
    return (0);
}
