#include "main.h"

int main(void)
{
	int size = 128;
	char *prompt = malloc(sizeof(char) * size);

	if (prompt == NULL)
	{
		return (NULL);
	}
	while (1)
	{
		prompter();
		input_text(prompt, sizeof(prompt));

	}
}
