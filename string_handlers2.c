#include "shell.h"


/**
 * _putchar - writes a char to stdout
 * @target_char: character to be printed
 *
 * Return: 1 (success), -1 (error)
 */
int _putchar(char target_char)
{
	static int idx;
	static char buf[WRITE_BUF_SIZE];

	if (target_char == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(1, buf, idx);
		idx = 0;
	}
	if (target_char != BUF_FLUSH)
		buf[idx++] = target_char;
	return (1);
}


/**
 *_puts - handles printing string from input
 *@str: string being printed
 *
 * Return: nil
 */
void _puts(char *str)
{
	int idx = 0;

	if (!str)
		return;
	while (str[idx] != '\0')
	{
		_putchar(str[idx]);
		idx++;
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

	if (dest_str == src_str || src_str == 0)
		return (dest_str);
	while (src_str[idx])
	{
		dest_str[idx] = src_str[idx];
		idx++;
	}
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

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--str;
	return (result);
}
