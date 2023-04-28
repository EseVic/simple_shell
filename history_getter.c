#include "shell.h"

/**
 * load_history - reads command history
 * from a file and add it to a history buffer
 * @content: struct parameter
 *
 * Return: histcount (success), 0 (error)
 */
int load_history(sh_args *content)
{
	int index, last_newline = 0, linecount = 0;
	ssize_t fil_des, read_len, fil_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *history_file = get_hist_file_path(content);

	if (!history_file)
		return (0);

	fil_des = open(history_file, O_RDONLY);
	free(history_file);
	if (fil_des == -1)
		return (0);
	if (!fstat(fil_des, &file_stats))
		fil_size = file_stats.st_size;
	if (fil_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fil_size + 1));
	if (!buffer)
		return (0);
	read_len = read(fil_des, buffer, fil_size);
	buffer[fil_size] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(fil_des);
	for (index = 0; index < fil_size; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = 0;
			add_to_history(content, buffer + last_newline, linecount++);
			last_newline = index + 1;
		}
	if (last_newline != index)
		add_to_history(content, buffer + last_newline, linecount++);
	free(buffer);
	content->histcount = linecount;
	while (content->histcount-- >= HIST_MAX)
		delete_node_index(&(content->history), 0);
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
	ssize_t fil_des;
	char *history_file = get_hist_file_path(content);
	l_list *node = NULL;

	if (!history_file)
		return (-1);

	fil_des = open(history_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(history_file);
	if (fil_des == -1)
		return (-1);
	for (node = content->history; node; node = node->link)
	{
		write_string_to_fd(node->str, fil_des);
		write_car_to_fd('\n', fil_des);
	}
	write_car_to_fd(BUF_FLUSH, fil_des);
	close(fil_des);
	return (1);
}


/**
 * add_to_history - builds a history list by adding
 * a new node at the end of the linked list pointed to by
 *	content->history
 * @content: struct parameter
 * @buffer: buffer
 * @linecount: history linecount, histcount
 *
 * Return: 0
 */
int add_to_history(sh_args *content, char *buffer, int linecount)
{
	l_list *node = NULL;

	if (content->history)
		node = content->history;
	new_end_node(&node, buffer, linecount);

	if (!content->history)
		content->history = node;
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

	home = getenv_clone(content, "HOME=");
	if (!home)
		return (NULL);
	buffer = malloc(sizeof(char) * (len_of_str(home)
		+ len_of_str(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	str_cpy(buffer, home);
	concat_str(buffer, "/");
	concat_str(buffer, HIST_FILE);
	return (buffer);
}


/**
 * update_hist_node_numbrs - renumbers
 * the nodes in a linked list of history items
 * @content: struct parameter
 *
 * Return: total number of nodes in the linked list
 * (i.e. the new highest number assigned to a node, plus one)
 */
int update_hist_node_numbrs(sh_args *content)
{
	l_list *node = content->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->link;
	}
	return (content->histcount = i);
}
