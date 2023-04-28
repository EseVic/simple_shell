#include "shell.h"


/**
 * car_finder - searches for a particular character in a string and
 *	returns a pointer to the first occurrence of that character
 * @target_char: character being looked for
 * @str: string being checked
 *
 * Return: the character that was found in string *start_of_dest
 */
char *car_finder(char *str, char target_char)
{
	while (*str++ != '\0')
	{
		if (target_char == *str)
		{
			return (str);
		}
	}
	return (NULL);
}


/**
 * string_concat - concatenate a portion of one string, src, onto the
 *	end of another string, dest
 * @dest: destination string
 * @src: source string
 * @max_chars: maximum number of characters to copy from src
 *
 * Return: concatenated string
 */
char *string_concat(char *dest, char *src, int max_chars)
{
	int dest_index, source_index;
	char *start_of_dest = dest;

	dest_index = 0;
	source_index = 0;
	while (dest[dest_index] != '\0')
		dest_index++;
	while (src[source_index] != '\0' && source_index < max_chars)
	{
		dest[dest_index] = src[source_index];
		dest_index++;
		source_index++;
	}
	if (source_index < max_chars)
		dest[dest_index] = '\0';
	return (start_of_dest);
}


/**
 * cpy_str - copies characters from the source string (src) to the
 *	destination string (dest) and ensure that the destination
 *	string is null-terminated
 * @dest: destination string
 * @src: source string
 * @limit: maximum number of characters to copy from src
 *
 * Return: copied string
 */
char *cpy_str(char *dest, char *src, int limit)
{
	int src_idx, dest_idx;
	char *dest_start = dest;

	src_idx = 0;
	while (src[src_idx] != '\0' && src_idx < limit - 1)
	{
		dest[src_idx] = src[src_idx];
		src_idx++;
	}
	if (src_idx < limit)
	{
		dest_idx = src_idx;
		while (dest_idx < limit)
		{
			dest[dest_idx] = '\0';
			dest_idx++;
		}
	}
	return (dest_start);
}


/**
 * coments_remover - searches and replaces first instance of '#' with '\0'
 * @text: string to be modifed
 *
 * Return: 0
 */
void coments_remover(char *text)
{
	int idx;

	for (idx = 0; text[idx] != '\0'; idx++)
		if (text[idx] == '#' && (!idx || text[idx - 1] == ' '))
		{
			text[idx] = '\0';
			break;
		}
}


/**
 * custom_itoa - converts a long integer num into a string
 *	representation in a given base, which can be specified through the flags
 * @num: number
 * @conversionBase: conversionBase
 * @flags: flags
 *
 * Return: converted string
 */
char *custom_itoa(long int num, int conversionBase, int flags)
{
	static char *conversionArray;
	static char conversionBuffer[50];
	char negativeSign = 0;
	char *currentChar;
	unsigned long unsignedNumber = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		unsignedNumber = -num;
		negativeSign = '-';

	}
	conversionArray = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	currentChar = &conversionBuffer[49];
	*currentChar = '\0';

	do	{
		*--currentChar = conversionArray[unsignedNumber % conversionBase];
		unsignedNumber /= conversionBase;
	} while (unsignedNumber != 0);

	if (negativeSign)
		*--currentChar = negativeSign;
	return (currentChar);
}
