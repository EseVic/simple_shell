#include "shell.h"

/**
 * fill_sh_args - sets the fname field of the struct to the name
 *	of the command being executed
 * @content: struct parameter
 * @arg_v: argument vector
 */
void fill_sh_args(sh_args *content, char **arg_v)
{
	int index = 0;

	content->fname = arg_v[0];
	if (content->arg)
	{
		content->argv = custom_strtow(content->arg, " \t");
		if (!content->argv)
		{

			content->argv = malloc(sizeof(char *) * 2);
			if (content->argv)
			{
				content->argv[0] = str_dup(content->arg);
				content->argv[1] = NULL;
			}
		}
		for (index = 0; content->argv && content->argv[index]; index++)
			;
		content->argc = index;

		replace_alias_with_value(content);
		replace_var_values(content);
	}
}


/**
 * reset_sh_args - resets the values of the fields in that struct
 *	to their default values
 * @content: struct parameter
 */
void reset_sh_args(sh_args *content)
{
	content->arg = NULL;
	content->argv = NULL;
	content->path = NULL;
	content->argc = 0;
}


/**
 * free_sh_args - frees sh_args fields
 * @content: struct parameter
 * @fields: fields
 */
void free_sh_args(sh_args *content, int fields)
{
	multi_free(content->argv);
	content->argv = NULL;
	content->path = NULL;
	if (fields)
	{
		if (!content->cmd_buf)
			free(content->arg);
		if (content->env)
			free_l_list(&(content->env));
		if (content->history)
			free_l_list(&(content->history));
		if (content->alias)
			free_l_list(&(content->alias));
		multi_free(content->environ);
			content->environ = NULL;
		free_n_NULL((void **)content->cmd_buf);
		if (content->readfd > 2)
			close(content->readfd);
		_putchar(BUF_FLUSH);
	}
}
