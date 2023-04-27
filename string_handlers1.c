#include "shell.h"


/**
 * find_substr_at_start - the string str_to_search starts with
 * the substring substring
 * @str_to_search: searched string
 * @substring: substring being searched
 *
 * Return: address of next char of str_to_search or NULL
 */
char *find_substr_at_start(const char *str_to_search, const char *substring)
{
	/* Iterate through the substring until the end */
	/* of the substring is reached */
	/* while also iterating through the string to search */
	for (; *substring != '\0'; substring++, str_to_search++)
	{
		/* If the current character in the substring */
		/* doesn't match the current */
		/* character in the string to search, return NULL */
		/* (no match found) */
		if (*substring != *str_to_search)
		{
			return (NULL);
		}
	}
	return ((char *)str_to_search);
}


/**
 * len_of_str - gets length of a string
 * @str: string length to be checked
 *
 * Return: string length
 */
int len_of_str(char *str)
{
	int idx = 0;
	/* Keep incrementing the index until the end of */
	/* the string is reached */
	while (str[idx] != '\0')
		idx++;

	return (idx);
}


/**
 * concat_str - concatenates strings str_dest and str_src
 * @str_dest: the destination buffer
 * @str_src: the source buffer
 *
 * Return: concatenates string
 */
char *concat_str(char *str_dest, char *str_src)
{
	char *result;

	result = str_dest;

	/* find the end of str_dest */
	do {
		str_dest++;
	} while (*str_dest != '\0');

	/* concatenate str_src to str_dest */
	do {
		*str_dest++ = *str_src++;
	} while (*str_dest != '\0');

	*str_dest = *str_src;
	return (result);
}


/**
 * cmpare_strs - compare two strings, str1 and str2, and
 *	return an integer value indicating their relative order
 * @str1: first string
 * @str2: second string
 *
 * Return: 0 (if str1 == str2), negative (str1 < str2), positive (str1 > str2)
 */
int cmpare_strs(char *str1, char *str2)
{
	/* Loop through both strings until one of them reaches its end */
	for ( ; *str1 && *str2; str1++, str2++)
	{
		/* If the characters at the current position */
		/* are not equal, return the difference between them */
		if (*str1 != *str2)
			return (*str1 - *str2);
	}

	/* If both strings are equal up to the length of the */
	/* shorter string, return zero */
	if (*str1 == *str2)
		return (0);
	/* Otherwise, return -1 if str1 is less than str2, or 1 */
	/* if str1 is greater than str2 */
	else
		return (*str1 < *str2 ? -1 : 1);
}
