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
	char **substrings;
	int idx_curr_substring = 0;
	int idx_curr_char = 0;
	int word_count = 0;
	int idx_curr_word = 0;
	int idx_curr_charInSubstring = 0;

	if (delimiter == NULL)
	{
		delimiter = " ";
	}

	/* Check if the string is empty */
	if (str[0] == 0 || str == NULL)
	{
		return (NULL);
	}

	idx_curr_char = 0;
	while (str[idx_curr_char] != '\0')
	{
		/* If the current character is not a delimiter and the next character is either */
		/* a delimiter or the end of the string, then the current character is the end of a word */
		if (!is_delimiter(str[idx_curr_char], delimiter) && (is_delimiter(str[idx_curr_char + 1], delimiter) || !str[idx_curr_char + 1]))
		{
			word_count++;
		}
		idx_curr_char++;
	}

	if (word_count == 0)
	{
		return (NULL);
	}

	substrings = malloc((1 + word_count) * sizeof(char *));
	if (substrings == NULL)
	{
		return (NULL);
	}
	
	idx_curr_char = 0;
	idx_curr_substring = 0;

	/* Iterate over the string and split it into words */
	while (idx_curr_substring < word_count)
	{
		/* Skip delimiters */
		for (; is_delimiter(str[idx_curr_char], delimiter); idx_curr_char++);

		/* Get the length of the current word */
		idx_curr_word = 0;
		for (; !is_delimiter(str[idx_curr_char + idx_curr_word], delimiter) && str[idx_curr_char + idx_curr_word]; idx_curr_word++);

		substrings[idx_curr_substring] = malloc((idx_curr_word + 1) * sizeof(char));
		if (substrings[idx_curr_substring] == NULL)
		{
			/* Free the allocated memory for the previous words */
			idx_curr_word = 0;
			while (idx_curr_word < idx_curr_substring)
			{
				free(substrings[idx_curr_word]);
				idx_curr_word++;
			}
			free(substrings);
			return (NULL);
		}

		/* Copy the current word to the substring */
		idx_curr_charInSubstring = 0;
		while (idx_curr_charInSubstring < idx_curr_word)
		{
			substrings[idx_curr_substring][idx_curr_charInSubstring] = str[idx_curr_char++];
			idx_curr_charInSubstring++;
		}

		substrings[idx_curr_substring][idx_curr_charInSubstring] = 0;

		idx_curr_substring++;
	}

	/* Terminate the array of substrings */
	substrings[idx_curr_substring] = NULL;
	return (substrings);
}



/**
 * handle_sigInt - handle signal calls when user presses Ctrl+C
 * @unused_signal_num:  indicates the signal number that
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

