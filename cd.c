#include "main.h"
/**
 * cust_cd - Changes directory according to path
 * @path: The path to the directory to change to.
 * Return: 0 on success, -1 on failure.
 */
int cust_cd(char *path)
{
    if (path == NULL)
        path = getenv("HOME");
        if (path == NULL)
            perror("Unable to change path");
            return (-1);
        else
            return(0);
    else if (chdir(path) != 0)
    {
        perror("Error");
        return (-1);
    }
    return (0);
}
