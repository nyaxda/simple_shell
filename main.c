#include "main.h"

int main(void)
{
	size_t buf_size = 0;
	char *buf = NULL;

	while (1)
	{
		getline(&buf, &buf_size, stdin);
	}
	return (0);
}
