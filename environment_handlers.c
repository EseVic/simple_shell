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
	int xx = 0, yy = 1;

	/* check if number of arguments is correct */
	if (content->argc != 3)
	{
		/* if number of arguments is incorrect, print error message */
		write_string_with_buffer("Error in number of arguements\n");
		return (yy);
	}

	/* if arguments are correct, try to set env var using env_setter function */
	if (env_setter(content, content->argv[1], content->argv[2]))
	{
		return (xx);
	}
	return (yy);
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
	int idx;

	if (content->argc == 1)
	{
		/* Prints errors */
		write_string_with_buffer("Too few arguements.\n");
		return (1);
	}

	for (idx = 1; idx <= content->argc; idx++)
	{
		/* calls d unsetenv_clone function with d args in the struct sh_args */
		/* and the command-line argument at the current index */
		unsetenv_clone(content, content->argv[idx]);
	}
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
	size_t idx;
	l_list *node = NULL;

	for (idx = 0; environ[idx]; idx++)
	{
		new_end_node(&node, environ[idx], 0);
	}

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
	int xx = 0;
	/* Extract the environment variables from d sh_args struct and prints */
	prnt_l_list_str(content->env);

	return (xx);
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
	char *ptr;
	l_list *node;

	node = content->env;

	while (node)
	{
		ptr = find_substr_at_start(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->link;
	}

	return (NULL);
}
