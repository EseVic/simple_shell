#include "shell.h"

/**
 * print_command_hist -  print out the command history,
 * consecutively, leading with line numbers, from 0
 * @content: struct parameter
 * Return: Always 0
 */
int print_command_hist(sh_args *content)
{
	/* get the history linked list */
	l_list *history = content->history;

	/* print the history with their indices */
	prnt_l_list_with_index(history);

	return (0);
}

