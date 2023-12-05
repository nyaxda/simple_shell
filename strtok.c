#include "main.h"

char *cust_strtk(char *string, const char *dlm)
{
    static char *pointer = NULL;
    char *tkn;

    if(string != NULL)
    {
        pointer = string;
    }
    else
    {
        if (pointer == NULL || *pointer == '\0')
        {
            return (NULL);
        }
    }
    for (; *pointer != '\0' && _strchr(dlm, *pointer) != NULL; pointer++)
    {

    }
    tkn = pointer;
    while (*pointer != '\0' && _strchr(dlm, *pointer) == NULL)
    {
        pointer++;
    }

    if (*pointer != '\0')
    {
        *pointer = '\0';
        pointer++;
    }
    return tkn;
}
