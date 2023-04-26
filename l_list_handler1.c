#include "shell.h"


/**
 * find_node_index - finds the index of a given node in a linked list
 * @head: head node
 * @target_node: target_node
 *
 * Return: node index starting from 0, -1 (otherwise)
 */
ssize_t find_node_index(l_list *head, l_list *target_node)
{
	l_list *current = head;
	ssize_t index = 0;

	/* Traverse the linked list until the current node is NULL */
	while (current != NULL)
	{

		/* Check if the current node matches the target node */
		if (current == target_node)
		{
			return (index);
		}

		index++;
		current = current->link;
	}
	return (-1);
}


/**
 * get_first_node_with_prefix -  searches a linked list of strings
 *	for the first node whose string starts with a given prefix
 * @node: pointer to list head
 * @search_str: string to match
 * @search_char: the next character after search_str to match
 *
 * Return: matching node, null
 */
l_list *get_first_node_with_prefix(l_list *node,
		char *search_str, char search_char)
{
	while (node)
	{
		if (strncmp(node->str, search_str, strlen(search_str)) == 0)
		{
			if (search_char == -1 || node->str[0] == search_char)
			{
				/* If the prefix and optional character match, return the current node */
				return (node);
			}
		}
		node = node->link;
	}
	return (NULL);
}


/**
 * list_len - finds length of linked list
 * @head: head node
 *
 * Return: list size
 */
size_t list_len(const l_list *head)
{
	if (head == NULL)
	{
		return (0);
	}
	else
	{
		return (1 + list_len(head->link));
	}
}


/**
 * prnt_l_list_with_index - prints all elements of a l_list linked list
 * @head: head node
 *
 * Return: list size
 */
size_t prnt_l_list_with_index(const l_list *head)
{
	size_t index = 0;
	const l_list *temp = head;

	if (temp != NULL)
	{
		do {
			/* Convert the integer value of the node to string and print it */
			_puts(custom_itoa(temp->num, 10, 0));
			_putchar(':');
			_putchar(' ');
			/* Print the string value of the node or "(nil)" if it's null */
			_puts(temp->str ? temp->str : "(nil)");
			_puts("\n");

			temp = temp->link;
			index++;
		} while (temp != NULL);
	}

	return (index);
}


/**
 * conv_list_to_strings - create an array of strings from list->str
 * @head: head node
 *
 * Return: array of strings
 */
char **conv_list_to_strings(l_list *head)
{
	char **str_array;
	char *str;
	l_list *node = head;
	size_t free_idx = 0;
	size_t index = list_len(head);

	if (!index || !head)
	{
		return (NULL);
	}

	str_array = malloc(sizeof(char *) * (index + 1));
	if (!str_array)
	{
		return (NULL);
	}
	for (index = 0; node; node = node->link, index++)
	{
		str = malloc(len_of_str(node->str) + 1);
		if (!str)
		{
			while (free_idx < index)
			{
				free(str_array[free_idx]);
				free_idx++;
			}
			free(str_array);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		str_array[index] = str;
	}
	str_array[index] = NULL;
	return (str_array);
}
