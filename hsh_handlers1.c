#include "shell.h"

/**
 * is_interactive - checks if shell is in interactive mode
 * @content: struct parameter
 *
 * Return: 1 (is interactive mode)
 */
int is_interactive(sh_args *content)
{
	/* Check if stdin is connected to a terminal */
    int is_stdin_tty = isatty(STDIN_FILENO);

	/* Check if the file descriptor for the shell's input is less than */
	/* or equal to 2 (stdin, stdout, or stderr) */
    int is_readfd_valid = content->readfd <= 2;

    return (is_stdin_tty && is_readfd_valid);
}


/**
 * is_delimiter - checks if a given character is a delimeter character
 * @car: character being check
 * @delimiter: delimeter string
 * 
 * Return: 1 (true), 0 (false)
 */
int is_delimiter(char car, char *delim)
{
	size_t idx;

	/* Iterate over the delimiter string until a null terminator is reached */
    for (idx = 0; delim[idx]; ++idx)
	{
		/* If the current delimiter matches the given character, return true */
        if (car == delim[idx])
		{
            return 1;
        }
    }

	/* If no delimiter matches the given character, return false */
    return 0;
}
