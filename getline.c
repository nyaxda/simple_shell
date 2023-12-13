#include "main.h"

/**
 * cust_getline - custom getline function
 * @pointer: buffer to store string.
 * @n: size in bytes of the buffer.
 * @strm: stream to read from.
 * Return: number of bytes read., -1 on failure.
*/
static char buffer[BUFFER];
static size_t buff_offset;
ssize_t cust_getline(char **pointer, size_t *n, FILE *strm)
{
    size_t data_size, result;

   while (1) 
   {
    	if (buff_offset == BUFFER_SIZE)
        	buff_offset = 0;

    	if (fgets(buffer + buff_offset, BUFFER_SIZE - buff_offset, strm) == NULL) 
        	break;

    	data_size = strlen(buffer + buff_offset);

    	if (buffer[buff_offset + data_size - 1] == '\n')
        break;
		else
        buff_offset += data_size;
	}

*pointer = buffer;
*n = buff_offset;
result = (ssize_t)buff_offset;
buff_offset = 0; 

return (result);
}