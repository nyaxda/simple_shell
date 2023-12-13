#include "main.h"

/**
 * cust_realoc -  creates reallocates a memory block using malloc and free.
 *
 *@ptr: pointer to the memory previously allocated with a call to malloc.
 *@old_size: old size of the allocated space for ptr in bytes.
 *@new_size: new size of the new memory block in bytes.
 *
 * Return: NULL.
 */
void *cust_realoc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *m;
	char *copy, *f;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		m = malloc(new_size);

		if (m == NULL)
			return (NULL);

		return (m);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	copy = ptr;
	m = malloc(sizeof(*copy) * new_size);

	if (m == NULL)
	{
		free(ptr);
		return (NULL);
	}

	f = m;

	for (i = 0; i < old_size && i < new_size; i++)
	{
		f[i] = *copy++;
	}
	free(ptr);
	return (m);
}