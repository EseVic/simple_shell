#include "shell.h"


/**
 * find_exec_path - finds the full path of a command within
 *	a list of directories provided in the dirctry_list
 * @content: struct content
 * @dirctry_list: string path
 * @command: command
 *
 * Return: command's full path | NULL
 */
char *find_exec_path(sh_args *content, char *dirctry_list, char *command)
{
	char *full_path;
	int path_index = 0;
	int prev_index = 0;

	if (!dirctry_list)
		return (NULL);
	if (find_substr_at_start(command, "./") && (len_of_str(command) > 2))
	{
		if (is_file_exec(content, command))
			return (command);
	}
	while (1)
	{
		if (!dirctry_list[path_index] || dirctry_list[path_index] == ':')
		{
			full_path = copy_chars_without_delimiter(dirctry_list,
					prev_index, path_index);
			if (!*full_path)
				concat_str(full_path, command);
			else
			{
				concat_str(full_path, "/");
				concat_str(full_path, command);
			}

			if (is_file_exec(content, full_path))
				return (full_path);

			if (!dirctry_list[path_index])
				break;
			/* Otherwise, update prev_index to path_index */
			prev_index = path_index;
		}
		path_index++;
	}
	return (NULL);
}


/**
 * is_file_exec - checks if a file is an executable command or not
 * @content: struct content
 * @file_path: file path
 *
 * Return: 1 (true), 0 (otherwise)
 */
int is_file_exec(sh_args *content, char *file_path)
{
	struct stat file_info;

	/* Ignore the 'content' parameter (unused) */
	(void)content;

	/* If the file path is null or the stat() function fails, return 0 */
	if (stat(file_path, &file_info) || !file_path)
	{
		return (0);
	}

	/* If the file is a regular file, return 1 */
	if (file_info.st_mode & S_IFREG)
		return (1);

	return (0);
}


/**
 * copy_chars_without_delimiter - duplicates chars while
 *	removing any delimiters
 * @pathstr: string path
 * @start_index: start index
 * @stop_index: stop index
 *
 * Return: pointer to new buffer
 */
char *copy_chars_without_delimiter(char *pathstr,
		int start_index, int stop_index)
{
	static char buffer[1024];
	int dest_index = 0;
	int source_index = 0;

	source_index = start_index;
	/* loop through each character in the string within the given range */
	while (source_index < stop_index)
	{
		/* check if the current character is not a delimiter (':') */
		if (pathstr[source_index] != ':')
		{
			/* copy if the current character is not a delimiter */
			buffer[dest_index] = pathstr[source_index];

			/* move to the next position in the buffer array */
			dest_index++;
		}
		/* move to the next character in the string */
		source_index++;
	}

	/* add null term at end of the copied characters in the buffer array */
	buffer[dest_index] = 0;
	return (buffer);
}
