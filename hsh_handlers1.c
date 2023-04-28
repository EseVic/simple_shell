#include "shell.h"

/**
 * is_interactive - checks if shell is in interactive mode
 * @content: struct parameter
 *
 * Return: 1 (is interactive mode)
 */
int is_interactive(sh_args *content)
{
	return (isatty(STDIN_FILENO) && content->readfd <= 2);
}


/**
 * is_delimiter - checks if a given
 * character is a delimeter character
 * @car: character being check
 * @delim: delimeter string
 *
 * Return: 1 (true), 0 (false)
 */
int is_delimiter(char car, char *delim)
{
	while (*delim)
		if (*delim++ == car)
			return (1);
	return (0);
}
