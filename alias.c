#include "shell.h"


/**
 * alias_to_str - convert an alias command in the
 * form "alias name=value"into a string and
 * store it in the "sh_args" struct
 * @content: struct parameter
 * @str: the alias string
 * Desc: It facilitates the creation of a new alias and
 * stores it in @content, but if the value of the alias is
 * not empty, the function calls @remv_alias with the to remove
 * any existing alias with the same name as the one being created
 * and then adds it as new node at the end of a linked list
 *
 * Return: 0 (success), 1 (error)
 */
int alias_to_str(sh_args *content, char *str)
{
	char *str_p;

	str_p = car_finder(str, '=');

	if (str_p == NULL)
	{
		return (1);
	}

	if (!*++str_p)
	{
		return (remv_alias(content, str));
	}

	remv_alias(content, str);

	return (new_end_node(&(content->alias), str, 0) == NULL);
}


/**
 * remv_alias - removes an alias command in the form
 * "alias name=value" from "sh_args" struct
 * @content: struct parameter
 * @str: the alias string
 * Desc: It copies alias name from @str_p to @copy, then
 * set @str_p to null (\0) to terminate the string at that point.
 * The find_node_index function is then called to find the index
 * of the node in the alias linked list that starts with the string
 * before the equal sign. The get_first_node_with_prefix function is
 * used to perform the comparison. If a matching node is found, the
 * delete_node_index function is called
 * to remove the node from the linked list.
 *
 * Return: 0 (success), 1 (error)7
 */
int remv_alias(sh_args *content, char *str)
{
	char *str_p, copy;
	int remover;

	str_p = car_finder(str, '=');
	if (!str_p)
		return (1);
	*copy = *str_p;
	*str_p = 0;
	remover = delete_node_index(&(content->alias),
		find_node_index(content->alias, get_first_node
			_with_prefix(content->alias, str, -1)));
	*str_p = copy;
	return (remover);
}


/**
 * alias_printer - prints the alias and
 * its value stored in the input node's "str"
 * @node: node of the alias
 *
 * Return: 0 (success), 1 (error)
 */
int alias_printer(l_list *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = car_finder(node->str, '=');
		/* printing chars before "=" */
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		/* printing the remaining chars after "=" */
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_clone - prints out the name and value of each alias
 * @content: struct parameter
 *
 *  Return: 0
 */
int alias_clone(sh_args *content)
{
	int i = 0;
	char *p = NULL;
	l_list *node = NULL;

	if (content->argc == 1)
	{
		/* prints the node while iterating through the linked list */
		node = content->alias;
		while (node)
		{
			alias_printer(node);
			node = node->link;
		}
		return (0);
	}

	for (i = 1; content->argv[i]; i++)
	{
		p = car_finder(content->argv[i], '=');
		if (p)
			alias_to_str(content, content->argv[i]);
		else
			alias_printer(get_first_node_with_prefix(
				content->alias, content->argv[i], '='));
	}

	return (0);
}
