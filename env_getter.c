#include "shell.h"


/**
 * env_setter - sets or updates an environment
 * variable with a given name and value
 * @content: struct parameter
 * @name: the name of the environment variable to be set
 * @value: the value of the environment variable to be set
 * Desc: It concatenates the name and value of the environment
 * variable, along with the equal sign, into the buffer then looks
 * for an existing variable with the same name as the one being set.
 * If it finds a matching variable, it frees the existing string for
 * that variable and replaces it with the new string in the buffer,
 * then it sets a flag indicating that the environment has been changed
 * "content->env_vars_changed" If it does not find a matching variable,
 * it adds a new node to the end of the linked list of environment
 * variables, with the new string in  the buffer as its value.
 *
 * Return: Always 0
 */
int env_setter(sh_args *content, char *name, char *value)
{
	char *buffer = NULL;
	char *str;
	l_list *node;

	if (!value || !name)
	{
		return (0);
	}

	/* allocates memory for a buffer that is large*/
	/* enough to hold the name and value of the */
	/* environment variable, plus an equal sign and a null terminator. */
	buffer = malloc(len_of_str(name) + len_of_str(value) + 2);
	if (!buffer)
	{
		return (1);
	}
	str_cpy(buffer, name);
	concat_str(buffer, "=");
	concat_str(buffer, value);

	/* Traverse the linked list of environment variables to find */
	/* the variable with the same name as the given name */
	node = content->env;
	for ( ; node; node = node->link)
	{
		str = find_substr_at_start(node->str, name);
		if (str && *str == '=')
		{
		/* If the variable is found, replace its value with the new value */
			free(node->str);
			node->str = buffer;
			content->env_changed = 1;
			return (0);
		}
	}
	new_end_node(&(content->env), buffer, 0);
	free(buffer);
	content->env_changed = 1;
	return (0);
}

/**
 * unsetenv_clone - to remove a variable from the environment
 * @content: struct parameter
 * @var: name of the variable to remove from the environment
 * Desc: Each node in the list contains a string that represents
 * a single environment variable in the format VARNAME=VALUE.
 * "find_substr_at_start" checks if the node's string starts
 * with var, is non-null, then the node represents the environment
 * variable to remove. The function calls delete_node_index to
 * remove the node from the linked list, sets content->env_vars_changed
 * to true to indicate that the environment was modified,resets the
 * index to 0, and starts iterating the linked list from the
 * beginning again. But if it is null, then the node does not
 * represent the environment variable to remove. The function
 * increments the index and  continues iterating the linked list
 *
 * Return: 1 (delete), 0 (if node or var is null,
 * indicating that no changes were made to the environment)
 */
int unsetenv_clone(sh_args *content, char *var)
{
	/* represents the current environment variables */
	char *ptr;
	l_list *node;
	size_t index = 0;

	/* Set the linked list node to the first node*/
	/* in the environment variables list */
	node = content->env;

	if (!var || !node)
	{
		return (0);
	}

	/* Loop through the linked list of environment*/
	/* variables until the end of the list is reached */
	do {
		/* Find the first occurrence of the input string at */
		/* the start of the current string in the linked list */
		ptr = find_substr_at_start(node->str, var);

		/* If the input string is found and there is an equals sign after it */
		if (ptr && *ptr == '=')
		{
			/* Delete the current node from the linked list,*/
				/*set env_vars_changed to 1 */
			/* and reset the index and node variables */
			content->env_changed = delete_node_index(&(content->env), index);
			index = 0;
			node = content->env;
			continue;
		}

		/* If the input string is not found or there is no*/
		/* equals sign after it move to the next node in*/
		/*the linked list and increment the index */
		node = node->link;
		index++;
	} while (node);
	return (content->env_changed);
}


/**
 * environ_getter - retrieve the current environment
 * variables as an array of strings and it caches it
 * @content: struct parameter
 * Desc: If the environ_vars field of the sh_args struct
 * is empty or has been changed since the last time environ_getter
 * was called, the function will convert the linked list of
 * environment variables in the env_list  field of the sh_args
 * struct to an array of strings using the conv_list_to_strings function
 * and store the resulting array in the environ_vars field.
 * The env_vars_changed field is then set to 0 to indicate that the
 * environment variables have not changed since the last call to environ_getter
 *
 * Return: 0
 */
char **environ_getter(sh_args *content)
{
	if (content->env_changed || !content->environ)
	{
		content->environ = conv_list_to_strings(content->env);

		/* reset the env_vars_changed flag */
		content->env_changed = 0;
	}
	return (content->environ);
}