#include "shell.h"

/**
 * load_history - reads command history from
 * a file and add it to a history buffer
 * @content: struct parameter
 *
 * Return: histcount (success), 0 (error)
 */
int load_history(sh_args *content)
{
	char *history_file_path;
	char *history_buffer;
	int del_idx;
	int idx = 0;
	int history_fil_des;
	int line_count = 0;
	int last_newline_index = 0;
	struct stat history_stat;
	ssize_t bytes_read;

	/* gets the path to the history file */
	history_file_path = get_hist_file_path(content);
	if (!history_file_path)
	{
		return (0);
	}

	/* opens the history file */
	history_fil_des = open(history_file_path, O_RDONLY);
	free(history_file_path);
	if (history_fil_des == -1)
	{
		return (0);
	}

	/* gets information about the history file */
	if (fstat(history_fil_des, &history_stat) == -1)
	{
		close(history_fil_des);
		return (0);
	}

	/* checks if history file is empty or too small */
	if (history_stat.st_size < 2)
	{
		close(history_fil_des);
		return (0);
	}

	history_buffer = (char*) malloc(history_stat.st_size + 1);
	if (!history_buffer)
	{
		close(history_fil_des);
		 return (0);
	}

	/* reads history file into buffer */
	bytes_read = read(history_fil_des, history_buffer, history_stat.st_size);
	history_buffer[history_stat.st_size] = '\0';
	close(history_fil_des);

	/* checks if history file was read successfully */
	if (bytes_read <= 0)
	{
		free(history_buffer);
		return (0);
	}

	/* iterates through history buffer and add entries to history linked list */
	while (idx < history_stat.st_size)
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
	if (last_newline_index != history_stat.st_size)
	{
		add_to_history(content, history_buffer + last_newline_index, line_count);
		line_count++
	}

	free(history_buffer);

	/* If the history list is too long, delete the oldest entry */
	for (del_idx = content->histcount; del_idx >= HIST_MAX; del_idx--)
	{
		delete_node_index(&(content->history), 0);
	}

	/* Update the history entry numbers */
	update_hist_node_numbrs(content);

	return (content->histcount);
}


/**
 * write_shel_histry - creates a file to store
 * history of shell program, or appends an existing file
 * @content: struct parameter
 *
 * Return: 1 (success), -1 (error)
 */
int write_shel_histry(sh_args *content)
{
	/* gets the path to the history file */
    char *history_file = get_hist_file_path(content);
    int file_des;
	l_list *node;

	if (!history_file)
	{
		return (-1);
	}

	/* Open the history file for writing*/
	/* truncating it if it exists, with 0644 permissions */
	file_des = open(history_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);

	free(history_file);

	if (file_des == -1)
	{
		return (-1);
	}

	/* Iterate through the history linked list*/
	/*and write each line to the file */
	node = content->history;
	while (node != NULL)
	{
		write_string_to_fd(node->str, file_des);
		write_car_to_fd('\n', file_des);
		node = node->link;
	}

	/* Write a flush character to the file to ensure all data is written */
	write_car_to_fd(BUF_FLUSH, file_des);
	close(file_des);

	return (1);
}


/**
 * add_to_history - builds a history list by adding a new node
 * at the end of the linked list pointed to by content->history
 * @content: struct parameter
 * @buffer: buffer
 * @linecount: history linecount, histcount
 *
 * Return: 0
 */
int add_to_history(sh_args *content, char *buffer, int linecount)
{
	l_list **tail_ptr = &(content->history);
	/* checks that the arguments are valid */
	if (content == NULL || buffer == NULL)
	return (-1);

	/* traverses the linked list until we reach the end */
	for ( ; *tail_ptr != NULL; tail_ptr = &((*tail_ptr)->link));

	/* creates a new node and add it to the end of the list */
	new_end_node(tail_ptr, buffer, linecount);
	return (0);
}


/**
 * get_hist_file_path - gets the path to the history file
 * @content: struct parameter
 *
 * Return: string construct to the path of the history file
 */
char *get_hist_file_path(sh_args *content)
{
	char *buffer, *home;


	/* Get the value of the HOME environment variable */
	home = getenv_clone(content, "HOME=");
	if (home == NULL)
	{
		return (NULL);
	}

	/* Calculate the lenght of the buffr needed to store the path*/
	buffer = malloc(sizeof(char) * (len_of_str(home)
		+ len_of_str(HIST_FILE) + 2));
	if (buffer == NULL)
	{
		return (NULL);
	}

	buffer[0] = 0;

	/* Copy the home directory path to the buffer */
	str_cpy(buffer, home);

	/* Add a '/' character to the end of the path */
	concat_str(buffer, "/");

	/* Copy the history file name to the buffer, starting after the '/' */
	concat_str(buffer, HIST_FILE);
	return (buffer);
}


/**
 * update_hist_node_numbrs - renumbers the
 * nodes in a linked list of history items
 * @content: struct parameter
 *
 * Return: total number of nodes in the linked list
 * (i.e. the new highest number assigned to a node, plus one)
 */
int update_hist_node_numbrs(sh_args *content)
{
	int idx = 0;
	l_list *node;

	/* Iterate through the linked list starting from the head node */
	for (node = content->history; node; node = node->link)
	node->num = idx++;

	/* Update the number of nodes in the linked list*/
	/* and return the total number of nodes */
	content->histcount = idx;
	return (idx);
}
