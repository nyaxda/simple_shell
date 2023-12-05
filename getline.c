#include "main.h"

/**
 * cust_getline - custom getline function
 * @pointer: buffer to store string.
 * @n: size in bytes of the buffer.
 * @strm: stream to read from.
 * Return: number of bytes read., -1 on failure.
*/
ssize_t cust_getline(char **pointer, size_t *n, FILE *strm)
{
	static char *buffer;
	static size_t buff_offset = 0;
	size_t buff_size = *n, data_size, rem_buff_size = *n, old_size, result;
	if (buffer == NULL)
	{
		buffer = malloc(sizeof(char) * (*n));
		if (buffer == NULL)
			return (-1);
	}
	while (fgets(buffer + buff_offset, rem_buff_size, strm) != NULL)
	{
		data_size = strlen(buffer + buff_offset);
		buff_offset += data_size;
		rem_buff_size = buff_size - buff_offset;

		if (buffer[buff_offset - 1] == '\n' || rem_buff_size <= 1)
		{
			if (rem_buff_size <= 1)
			{
				old_size = buff_size;
				buff_size *= INCREMENT_BUFFER_FACTOR;
				rem_buff_size = buff_size - buff_offset;
				buffer = cust_realoc(buffer, old_size, buff_size);
				if (buffer == NULL)
					return (-1);
			}
		}
		else
			break;
	}
	*pointer = buffer;
	*n = buff_size;
	result = (ssize_t) buff_offset;
	buff_offset = 0;
	return (result);
}
