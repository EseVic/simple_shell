#include "shell.h"


/**
 * **custom_strtow - takes a string (str) and a delimiter string
 *	(delimiter) as input and then split str into an array of strings
 * @str: the input string
 * @delimiter: the delimeter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *str, char *delimiter)
{
	int word_count = count_words(str, delimiter);
	char **substrings = allocate_substrings(word_count);

	if (word_count == 0)
		return (NULL);

	if (substrings == NULL)
		return (NULL);

	fill_substrings(str, delimiter, substrings, word_count);

	return (substrings);
}

/**
 * handle_sigInt - handle signal calls when user presses Ctrl+C
 * @unused_signal_num: indicates the signal number that
 *	triggered the signal handler
 *
 * Return: nil
 */
void handle_sigInt(__attribute__((unused))int unused_signal_num)
{
	/* handles promting to the cmd*/
	_puts("\n$ ");
	_putchar(BUF_FLUSH);
}
