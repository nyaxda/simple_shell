/**
 * freed - Frees the memory allocated for a dynamically allocated 2D array.
 * @array: The 2D array to be freed.
 * @size: The size of the array.
 * return: void.
 */
void freed(char **array, int size)
{
    for (int i = 0; i < size; ++i)
        free(array[i]);
    free(array);
}
