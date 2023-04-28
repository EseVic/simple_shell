#include "shell.h"


/**
 * prnt_l_list_str - print all the strings stored in a singly
 *	linked list of strings, with each string followed by a
 *	newline character
 * @head: first node pointer
 *
 * Return: number of nodes traversed in the linked list
 */
size_t prnt_l_list_str(const l_list *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->link;
		index++;
	}
	return (index);
}


/**
 * new_end_node - adds a new node to the end of a linked list
 * @list_head: head node
 * @str: strings
 * @num: index
 *
 * Return: list size
 */
l_list *new_end_node(l_list **list_head, const char *str, int num)
{
	l_list *new_node, *current_node;

	if (!list_head)
		return (NULL);

	current_node = *list_head;
	new_node = malloc(sizeof(l_list));
	if (!new_node)
		return (NULL);
	memset_clone((void *)new_node, 0, sizeof(l_list));
	new_node->num = num;
	if (str)
	{
		new_node->str = str_dup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->link)
			current_node = current_node->link;
		current_node->link = new_node;
	}
	else
		*list_head = new_node;
	return (new_node);
}


/**
 * delete_node_index - delete a node in a linked list at a specific index
 * @list_head: head node
 * @index: index node being deleted
 *
 * Return: 1 (success), 0 (failure)
 */
int delete_node_index(l_list **list_head, unsigned int index)
{
	l_list *current_node, *preceding_node;
	unsigned int x = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!index)
	{
		current_node = *list_head;
		*list_head = (*list_head)->link;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *list_head;
	while (current_node)
	{
		if (x == index)
		{
			preceding_node->link = current_node->link;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		x++;
		preceding_node = current_node;
		current_node = current_node->link;
	}
	return (0);
}


/**
 * free_l_list - frees all list
 * @list_head: head node
 *
 * Return: void
 */
void free_l_list(l_list **list_head)
{
	l_list *current_node, *next_node, *head;

	if (!list_head || !*list_head)
		return;
	head = *list_head;
	current_node = head;
	while (current_node)
	{
		next_node = current_node->link;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	*list_head = NULL;
}
