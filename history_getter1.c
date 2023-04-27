#include "shell.h"


/**
 * load_history - reads command history from
 *	a file and add it to a history buffer
 * @content: struct parameter
 *
 * Return: read_and_process_history (success)
 */
int load_history(sh_args *content)
{
	char *history_file_path;
	int history_fil_des;

	history_file_path = get_hist_file_path(content);
	if (!history_file_path)
		return (0);

	history_fil_des = open_history_file(history_file_path);
	free(history_file_path);
	if (history_fil_des == -1)
		return (0);

	return (read_and_process_history(content, history_fil_des));
}


/**
 * open_history_file - opens the history file and returns the file descriptor
 * @history_file_path: history file path
 *
 * Return: history_fil_des (success)
 */
int open_history_file(const char *history_file_path)
{
	int history_fil_des;

	history_fil_des = open(history_file_path, O_RDONLY);
	return (history_fil_des);
}


/**
 * read_and_process_history - reads and process the history file
 * @content: struct parameter
 * @history_fil_des: history_fil_des
 *
 * Return: histcount (success)
 */
int read_and_process_history(sh_args *content, int history_fil_des)
{
	struct stat history_stat;
	ssize_t bytes_read;
	char *history_buffer;

	if (fstat(history_fil_des, &history_stat) == -1)
	{
		close(history_fil_des);
		return (0);
	}

	if (history_stat.st_size < 2)
	{
		close(history_fil_des);
		return (0);
	}

	history_buffer = (char *)malloc(history_stat.st_size + 1);
	if (!history_buffer)
	{
		close(history_fil_des);
		return (0);
	}

	bytes_read = read(history_fil_des, history_buffer, history_stat.st_size);
	history_buffer[history_stat.st_size] = '\0';
	close(history_fil_des);

	if (bytes_read <= 0)
	{
		free(history_buffer);
		return (0);
	}

	parse_history(content, history_buffer, history_stat.st_size);
	free(history_buffer);

	trim_history(content);
	update_hist_node_numbrs(content);
	return (content->histcount);
}



/**
 * parse_history - adds entries to the history linked list
 * @content: struct parameter
 * @history_buffer: the load_history buffer
 * @buffer_size: the load_history buffer size
 *
 * Return: nil
 */
void parse_history(sh_args *content, char *history_buffer, size_t buffer_size)
{
	int del_idx;
	int idx = 0;
	int last_newline_index = 0;
	int line_count = 0;

	/* iterates through history buffer and add entries to history linked list */
	while (idx < buffer_size)
	{
		if (history_buffer[idx] == '\n')
		{
			history_buffer[idx] = '\0';
			add_to_history(content, history_buffer + last_newline_index, line_count);
			last_newline_index = idx + 1;
			line_count++;
		}
		idx++;
	}

	/* If there is still text in the buffer, add it as a new entry */
	if (last_newline_index != buffer_size)
	{
		add_to_history(content, history_buffer + last_newline_index, line_count);
		line_count++;
	}
}



/**
 * trim_history - trims the history linked list if its size exceeds
 * @content: struct parameter
 *
 * Return: nil
 */
void trim_history(sh_args *content)
{
	int del_idx;

	for (del_idx = content->histcount; del_idx >= HIST_MAX; del_idx--)
	{
		delete_node_index(&(content->history), 0);
	}
}
