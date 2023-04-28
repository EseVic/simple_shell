#include "shell.h"


/**
 * **custom_strtow - takes a string (str) and a delimiter string
 *	(delimiter) as input and then split str into an array of strings
 * @str: the input string
 * @delimiter: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *str, char *delimiter)
{
	int i, j, k, m, word_count = 0;
	char **substrings;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], delimiter) &&
				(is_delimiter(str[i + 1], delimiter) || !str[i + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	substrings = malloc((1 + word_count) * sizeof(char *));
	if (!substrings)
		return (NULL);
	for (i = 0, j = 0; j < word_count; j++)
	{
		while (is_delimiter(str[i], delimiter))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], delimiter) && str[i + k])
			k++;
		substrings[j] = malloc((k + 1) * sizeof(char));
		if (!substrings[j])
		{
			for (k = 0; k < j; k++)
				free(substrings[k]);
			free(substrings);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			substrings[j][m] = str[i++];
		substrings[j][m] = 0;
	}
	substrings[j] = NULL;
	return (substrings);
}
