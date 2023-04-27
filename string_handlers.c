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
	int idx = 0;
	/* Loop through the characters of the string until */
	/* a null character is found */
	for (idx = 0; str[idx] != '\0'; idx++)
	{
		/* Check if the current character matches the target character */
		if (str[idx] == target_char)
		{
			/* If the target character is found, return */
			/* a pointer to the current character in the string */
			return (&str[idx]);
		}
	}
	return (NULL);
}


/**
 * string_concat - concatenate a portion of one string, src,
 *	onto the end of another string, dest
 * @dest: destination string
 * @src: source string
 * @max_chars: maximum number of characters to copy from src
 *
 * Return: pointer to the beginning of the dest string
 */
char *string_concat(char *dest, char *src, int max_chars)
{
	/* Save the start of the destination string for returning later */
	char *start_of_dest = dest;

	/* Iterate to the end of the destination string */
	while (*dest)
	++dest;

	/* concatenates characters from the source string */
	/* to the destination string until the end of */
	/* the source string is reached or the maximum number of */
	/* characters has been concatenated */
	while (*src && max_chars--)
	{
		*dest++ = *src++;
	}

	/* Add a null terminator to the end of the concatenated string */
	*dest = '\0';

	/* pointer to the beginning of the destination string */
	return (start_of_dest);
}


/**
 * cpy_str - copies characters from the source string (src)
 *	to the destination string (dest) and ensure that the
 *	destination string is null-terminated
 * @dest: destination string
 * @src: source string
 * @limit: maximum number of characters to copy from src
 *
 * Return: copied string
 */
char *cpy_str(char *dest, char *src, int limit)
{
	char *dest_start;
	int dest_idx;
	int src_idx = 0;

	dest_start = dest;

	/* Copy characters from the source string to */
	/* the destination string until */
	/* the limit or the end of the source string is reached */
	for ( ; src_idx < limit - 1 && src[src_idx] != '\0'; src_idx++)
		dest[src_idx] = src[src_idx];

	/* If the index of the source string is less than */
	/* the limit, add null characters */
	/* to the destination string until the limit is reached */
	if (src_idx < limit)
	{
		for (dest_idx = src_idx; dest_idx < limit; dest_idx++)
		{
			dest[dest_idx] = '\0';
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
	int idx = 0;

	/* Loop through the string until a null terminator is found */
	while (text[idx] != '\0')
	{
		/* Check if the current character is a hash (#) */
		/* and the previous character is a space */
		/* or if the current character is a hash and it's */
		/* the first character in the string */
	if ((!idx || text[idx - 1] == ' ') && text[idx] == '#')
	{
			/* Replace the hash with a null terminator */
			/* to remove the comment */
		text[idx] = '\0';
		break;
	}
	idx++;
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
	char negativeSign = 0, *currentChar;
	static char *conversionArray, conversionBuffer[50];
	unsigned long unsignedNumber = num;

	/* If the input number is negative and the flag for */
	/* converting to unsigned is not set */
	/* set the negative sign and convert the absolute value */
	if (num < 0 && !(flags & CONVERT_UNSIGNED))
	{
		unsignedNumber = -num;
		negativeSign = '-';
	}

	/* Choose the conversion array based on the flag */
	/* for lowercase conversion */
	conversionArray = flags & CONVERT_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";

	/* Set the current character pointer to the end of the */
	/* conversion buffer */
	currentChar = &conversionBuffer[49];
	*currentChar = '\0';

	/* Perform the conversion, starting from the end */
	/* of the buffer and working backwards */
	do {
		*--currentChar = conversionArray[unsignedNumber % conversionBase];
		unsignedNumber /= conversionBase;
	} while (unsignedNumber != 0);

	/* If there is a negative sign, add it to the beginning */
	/* of the buffer */
	if (negativeSign)
	{
		*--currentChar = negativeSign;
	}

	return (currentChar);
}
