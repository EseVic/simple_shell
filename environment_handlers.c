#include "shell.h"

/**
 * check_env_setter - verifies the number of
 * arguments being passed to env_setter
 * @content: struct parameter
 *
 * Return: 0 (success), 1 (error)
 */
int check_env_setter(sh_args *content)
{
	int result = 1;

	/* check if number of arguments is correct */
	if (content->argc == 3)
	{
		/* if arguments are correct, try to set environment*/
		/* variable using env_setter function */
	if (!env_setter(content, content->argv[1], content->argv[2]))
	/* if env_setter returns 0, set result to 0*/
	/* indicating that environment variable could not be set */
		result = 0;
	}
	/* if number of arguments is incorrect, print error message */
	else
	 write_string_with_buffer("Incorrect number of arguments\n");

	return (result);
}


/**
 * check_env_unsetenv - verifies the number of
 *arguments being passed to env_setter unsetenv_clone
 * @content: struct parameter
 *
 * Return: 0
 */
int check_env_unsetenv(sh_args *content)
{
	int idx = 1;

	if (content->argc < 2)
	{
		write_string_with_buffer("too few arguments\n");
		return (1);
	}

	while (idx < content->argc)
	{
		/* calls the unsetenv_clone function with the arguments in the*/
		/* struct sh_args and the command-line argument at the current index */
		unsetenv_clone(content, content->argv[idx]);
	++idx;
	}
	return (0);
}


/**
 * populat_listof_env -  populating a linked list with environment variables
 * @content: struct parameter
 * Desc: it adds each element of the environ array to the end of
 * the linked list using the new_end_node function.The third
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
	/* Extract the environment variables from the sh_args struct and print them */
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

	/* Loop through the linked list until we reach the end or find a match */
	for ( ; node != NULL; node = node->link)
	{
		/* Search for the specified name at the start of the current string */
		p = find_substr_at_start(node->str, name);

		/* If a match is found, return the pointer to the matching substring */
		if (p && *p)
		{
			return (p);
		}
	}
	return (NULL);
}

