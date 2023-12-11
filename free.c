#include "main.h"

/**
 * freed - Frees the memory allocated for a dynamically allocated 2D array.
 * @array: The 2D array to be freed.
 * @size: The size of the array.
 * return: void.
 */
void freed(char **array)
{
    int i;
    if (array != NULL)
    {
        for (i = 0; array[i] != NULL; i++)
            free(array[i]);
        free(array);
    }
    array = NULL;
}

/**
 * charfree - Frees the memory allocated for a character string.
 * @str: The character string to be freed.
 */
void charfree(char *str)
{
    if (str != NULL)
    {
        free(str);
        str = NULL;
    }
}
