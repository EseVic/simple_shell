#include "shell.h"


/**
 * write_with_buffer - inputs characters from car to stderr
 * @car: The character to print
 *
 * Return: 1 (success), -1 (error)
 */
int write_with_buffer(char car)
{
	static char buffer[WRITE_BUF_SIZE];
	static int index;

	/* If the buffer is full or a flush character is received, */
	/* write the buffer to the output and reset the index to 0 */
	if (index >= WRITE_BUF_SIZE || car == BUF_FLUSH)
	{
		write(2, buffer, index);
		index = 0;
	}

	if (car != BUF_FLUSH)
	{
		buffer[index++] = car;
	}
	return (index);
}


/**
 * write_string_with_buffer - takes a string as input and
 * writes its contents to the output stream using a buffer
 * @str: string being printed to stdout
 *
 * Return: Nil
 */
void write_string_with_buffer(char *str)
{
	int index;

	index = 0;

	if (str == NULL)
	{
		return;
	}
	for (index = 0; str[index] != '\0'; index++)
		write_with_buffer(str[index]);
}
