#include "shell.h"


/**
 * prnt_l_list_str - print all the strings stored in a singly linked list
 *	of strings, with each string followed by a newline character
 * @head: first node pointer
 *
 * Return: number of nodes traversed in the linked list
 */
size_t prnt_l_list_str(const l_list *head)
{
	size_t index = 0;

	for ( ; head; index++)
	{
		/* Print the string value of the current node */
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");

		/* Move to the next node */
		head = head->link;
	}

	/* Return the total number of nodes printed */
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
	l_list *current_node = *list_head;
	l_list *new_node;

	if (!list_head)
	{
		return (NULL);
	}


	while (current_node && current_node->link)
	{
		current_node = current_node->link;
	}

	new_node = malloc(sizeof(l_list));

	if (!new_node)
	{
		return (NULL);
	}

	/* initialize new node's values to zero */
	memset_clone((void *)new_node, 0, sizeof(l_list));
	new_node->num = num;

	/* check if input str exists and duplicates it */
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
		current_node->link = new_node;
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
	unsigned int idx = 0;
	l_list *node_to_delete;
	l_list *preceding_node;

	if (!list_head || !*list_head)
	{
		return (0);
	}

	/* If the first node is to be deleted */
	if (index == 0)
	{
		node_to_delete = *list_head;
		*list_head = node_to_delete->link;
	}
	else
	{
		/* Traverse the list to find the node preceding the one to be deleted */
		preceding_node = *list_head;
		for ( ; idx < index - 1; idx++)
		{
			preceding_node = preceding_node->link;

			/* Check if index is out of bounds */
			if (!preceding_node)
			{
				return (0);
			}
		}
		node_to_delete = preceding_node->link;

		/* Check if index is out of bounds */
		if (!node_to_delete)
			return (0);
		preceding_node->link = node_to_delete->link;
	}

	free(node_to_delete->str);
	free(node_to_delete);
	return (1);
}


/**
 * free_l_list - frees all list
 * @list_head: head node
 *
 * Return: void
 */
void free_l_list(l_list **list_head)
{
	l_list *current_node;

	if (!*list_head || !list_head)
	{
		return;
	}

	for (current_node = *list_head; current_node != NULL; )
	{
		l_list *next_node = current_node->link;

		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}

	*list_head = NULL;
}
