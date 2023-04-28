#include "shell.h"


/**
 * check_env_setter - verifies the number of
 * arguments being passed to env_setter
 * @content: struct parameter
 *
 *  Return: 0 (success), 1 (error)
 */
int check_env_setter(sh_args *content)
{
	if (content->argc != 3)
	{
		write_string_with_buffer("Incorrect number of arguements\n");
		return (1);
	}
	if (env_setter(content, content->argv[1], content->argv[2]))
		return (0);
	return (1);
}

/**
 * check_env_unsetenv - verifies the number of
 * arguments being passed to env_setter unsetenv_clone
 * @content: struct parameter
 *
 *  Return: 0
 */
int check_env_unsetenv(sh_args *content)
{
	int index;

	if (content->argc == 1)
	{
		write_string_with_buffer("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= content->argc; index++)
		unsetenv_clone(content, content->argv[index]);

	return (0);
}

/**
 * populat_listof_env -  populating a linked list with environment variables
 * @content: struct parameter
 * Desc: it adds each element of the environ array to the end
 * of the linked list using the new_end_node function. The third
 * argument to new_end_node takes 0 (an integer value) as arguments
 *
 * Return: 0
 */
int populat_listof_env(sh_args *content)
{
	l_list *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		new_end_node(&node, environ[i], 0);
	content->env = node;
	return (0);
}


/**
 * env_clone - print the current environment variables of the program
 * @content: struct parameter
 *
 * Return: 0
 */
int env_clone(sh_args *content)
{
	prnt_l_list_str(content->env);
	return (0);
}


/**
 * getenv_clone - search for an environment variable with
 * the given name in the linked list pointed to by content->env
 * and return a pointer to its value if it is found
 * @content: struct parameter
 * @name: name of env var
 *
 * Return: the value
 */
char *getenv_clone(sh_args *content, const char *name)
{
	l_list *node = content->env;
	char *p;

	while (node)
	{
		p = find_substr_at_start(node->str, name);
		if (p && *p)
			return (p);
		node = node->link;
	}
	return (NULL);
}
