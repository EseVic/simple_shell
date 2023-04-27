#include "shell.h"


/**
 * count_words - counts the number of words in a string
 * @str:  input string
 * @delimiter: delimiter string
 *
 * Return: the number of words in the string
 */
int count_words(char *str, char *delimiter)
{
	int count = 0;
	int idx_curr_char = 0;

	while (str[idx_curr_char])
	{
		if (!is_delimiter(str[idx_curr_char], delimiter))
		{
			count++;
			while (!is_delimiter(str[idx_curr_char], delimiter) &&
				   str[idx_curr_char])
				idx_curr_char++;
		}
		else
		{
			idx_curr_char++;
		}
	}

	return (count);
}

/**
 * allocate_substrings - allocates memory for the substrings array
 * @word_count: the number of words in the string
 *
 * Return: a pointer to the allocated substrings array
 */
char **allocate_substrings(int word_count)
{
	char **substrings = malloc((1 + word_count) * sizeof(char *));

	if (substrings == NULL)
		return (NULL);

	return (substrings);
}

/**
 * fill_substrings - fills the substrings array with the split words
 * @str: the input string
 * @delimiter: the delimiter string
 * @substrings: the array of substrings
 * @word_count: the number of words in the string
 */
void fill_substrings(char *str, char *delimiter,
		char **substrings, int word_count)
{
	int idx_curr_substring = 0;
	int idx_curr_char = 0;
	int idx_curr_word, idx_curr_charInSubstring = 0;

	while (idx_curr_substring < word_count)
	{
		for ( ; is_delimiter(str[idx_curr_char],	delimiter);
				idx_curr_char++)
		{
		}
		idx_curr_word = 0;
		while (!is_delimiter(str[idx_curr_char + idx_curr_word], delimiter) &&
			   str[idx_curr_char + idx_curr_word])
		{
			idx_curr_word++;
		}
		substrings[idx_curr_substring] = malloc((idx_curr_word + 1) * sizeof(char));
		if (substrings[idx_curr_substring] == NULL)
		{
			idx_curr_word = 0;
			while (idx_curr_word < idx_curr_substring)
			{
				free(substrings[idx_curr_word]);
				idx_curr_word++;
			}
			free(substrings);
			return;
		}
		idx_curr_charInSubstring = 0;
		while (idx_curr_charInSubstring < idx_curr_word)
		{
			substrings[idx_curr_substring][idx_curr_charInSubstring] =
				str[idx_curr_char++];
			idx_curr_charInSubstring++;
		}
		substrings[idx_curr_substring][idx_curr_charInSubstring] = '\0';
		idx_curr_substring++;
	}

	substrings[idx_curr_substring] = NULL;
}
