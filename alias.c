#include "shell.h"


/**
 * alias_to_str - convert an alias command in the form "alias name=value"
 *	into a string and store it in the "sh_args" struct
 * @content: struct parameter
 * @str: the alias string
 * Desc: It facilitates the creation of a new alias and stores
 * it in @content, but if the value of the alias is not empty,
 * the function calls @remv_alias with the to remove any existing
 * alias with the same name as the one being created and then adds
 * it as new node at the end of a linked list
 *
 * Return: 0 (success), 1 (error)
 */
int alias_to_str(sh_args *content, char *str)
{
/* Find the equals sign in the string */
	char *str_p = car_finder(str, '=');

	if (str_p == NULL)
	return (1);

	/* If the value part of the alias is empty,*/
	/*remove the alias from the structure */

	if (*++str_p == '\0')
	{
	if (remv_alias(content, str))
		return (1);
	}

	/* If the value part of the alias is not empty,*/
	/*add or update the alias in the structure */
	else
	{
	remv_alias(content, str);

		/* Add the new alias to the end of the list */
	if (new_end_node(&(content->alias), str, 0) == NULL)
		return (1);
	}
	return (0);
}


/**
 * remv_alias - removes an alias command in the form "alias name=value"
 *		from "sh_args" struct
 * @content: struct parameter
 * @str: the alias string
 * Desc: It copies alias name from @str_p to @copy,
 * then set @str_p to null (\0) to terminate the string at that point.
 * The find_node_index function is then called to find the index of the
 * node in the alias linked list that starts with the string before the
 * equal sign. The get_first_node_with_prefix function is used to perform
 * the comparison. If a matching node is found, the delete_node_index
 * function is called to remove the node from the linked list.
 *
 * Return: 0 (success), 1 (error)
 */
int remv_alias(sh_args *content, char *str)
{
    /* Find the position of the '=' character in the input string */
	char *str_p = car_finder(str, '=');

	int remover, index;

	char copy = *str_p;

	if (!str_p)
	return (1);

    /* Temporarily replace the '=' character with a null terminator */
	*str_p = '\0';

 /* Get the index of the first node in the*/
  /* alias list that matches the prefix*/
	index = find_node_index(content->alias,
	get_first_node_with_prefix(content->alias, str, -1));

    /* Delete the node at the given index from the alias list */
	remover = delete_node_index(&(content->alias), index);

    /* Restore the '=' character to the input string */
	*str_p = copy;

	return (remover);
}


/**
 * alias_printer - prints the alias and its value
 *stored in the input node's "str"
 * @node: node of the alias
 *
 * Return: 0 (success), 1 (error)
 */
int alias_printer(l_list *node)
{
	char *c_ptr;
	char *equal_sign_ptr = car_finder(node->str, '=');

	if (!node)
	return (1);

	/* Printing chars before "="*/
	for (c_ptr = node->str; c_ptr != equal_sign_ptr; ++c_ptr)
		_putchar(*c_ptr);

	_putchar('\'');

	/* Printing the remaining chars after "=" */
	_puts(equal_sign_ptr + 1);
	_puts("'\n");

	return (0);
}


/**
 * alias_clone - prints out the name and value of each alias
 * @content: struct parameter
 *
 * Return: 0
 */
int alias_clone(sh_args *content)
{
	int i;

	if (content->argc == 1)
	{
	/* prints all nodes in the linked list */
		l_list *node = content->alias;

	while (node != NULL)
	{
		alias_printer(node);
		node = node->link;
	}
	}
	else
	{
	/* prints nodes in the linked list that match given aliases */
	for (i = 1; content->argv[i] != NULL; i++)
	{
		char *car = car_finder(content->argv[i], '=');
	if (car != NULL)
		alias_to_str(content, content->argv[i]);

	else
	{
		l_list *matching_node = get_first_node_with_prefix
		(content->alias, content->argv[i], '=');
		if (matching_node != NULL)
		alias_printer(matching_node);
	}
	}
	}
	return (0);
}

