#include "shell.h"


/**
 * _putchar - writes a char to stdout
 * @target_char: character to be printed
 *
 * Return: 1 (success), -1 (error)
 */
int _putchar(char target_char)
{
	static char buf[WRITE_BUF_SIZE];
	static int idx;

	/* Check if the buffer is full or a flush signal is received */
	if (target_char == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		/* Write the contents of the buffer to console */
		/* output and reset buffer */
		write(1, buf, idx);
		idx = 0;
	}

	/* If a flush signal is not received, add the character to */
	/* the buffer */
	if (target_char != BUF_FLUSH)
		buf[idx++] = target_char;
	return (1);
}


/**
 * _puts - handles printing string from input
 * @str: string being printed
 *
 * Return: nil
 */
void _puts(char *str)
{
	int idx = 0;

	if (str == NULL)
	{
		return;
	}

	/* Iterate over the string and write each character to */
	/* the console output */
	for ( ; str[idx] != '\0'; idx++)
	{
		_putchar(str[idx]);
	}
}


/**
 * str_cpy - copies string from src_str to dest_str
 * @dest_str: string destination
 * @src_str: string source
 *
 * Return: pointer to destination
 */
char *str_cpy(char *dest_str, char *src_str)
{
	int idx = 0;

	/* Check if the source string is null or if the */
	/* source and destination */
	/* strings are the same and if so, return the destination string */
	if (src_str == 0 || dest_str == src_str)
	{
		return (dest_str);
	}

	/* Copy characters from the source string to the destination string */
	while (src_str[idx])
	{
		dest_str[idx] = src_str[idx];
		idx++;
	}

	/* Add the null character at the end of the destination string */
	dest_str[idx] = 0;
	return (dest_str);
}


/**
 * str_dup - handles string duplication
 * @str: string being duplicated
 *
 * Return: pointer to the duplicated string
 */
char *str_dup(const char *str)
{
	int len = 0;
	char *result;

	/* Return NULL if str is empty */
	if (!str)
	{
		return (NULL);
	}

	/* Iterate over the string and count the number of characters */
	while (*str++)
	{
		len++;
	}

	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
	{
		return (NULL);
	}

	/* Iterate over the string in reverse and copy */
	/* the characters to the duplicated string */
	for (len++; len--;)
	{
		result[len] = *--str;
	}

	return (result);
}
