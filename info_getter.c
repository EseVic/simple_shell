include "shell.h"

/**
 * fill_sh_args - sets the fname field of the struct
 *	to the name of the command being executed
 * @content: struct parameter
 * @arg_v: argument vector
 */
void fill_sh_args(sh_args * content, char **arg_v)
{
	int index = 0;

	/* assign the first string in arg_v to fname field of sh_args struct */
	content->fname = arg_v[0];
	if (content->arg)
	{
		/* parse 2nd string in arg_v and assign to argv field of sh_args struct */
		content->argv = custom_strtow(content->arg, " \t");
		if (content->argv == NULL)
		{
			/* if the parsing fails, assign entire string to argv[0] */
			content->argv = (char **)malloc(2 * sizeof(char *));
			if (content->argv)
			{
				content->argv[0] = str_dup(content->arg);
				content->argv[1] = NULL;
			}
		}
		/* count number of strings in argv array */
		else
		{
			while (content->argv[index] != NULL)
			{
				/* Do nothing. Just counting */
				index++;
			}
		}

		/* assign number of strings to argc field of sh_args struct */
		content->argc = index;

		/* replace any aliases in argv strings with their respective values */
		replace_alias_with_value(content);

		/* replace any variables in argv strings with their respective values */
		replace_var_values(content);
	}
}


/**
 * reset_sh_args - resets the values of the fields in that
 *	struct to their default values
 * @content: struct parameter
 */
void reset_sh_args(sh_args *content)
{
	/* Set all the members of the struct to their default values */
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
		/* Free the arg buffer if it was dynamically allocated and cmd_buf is NULL */
		if (!content->cmd_buf)
		{
			free(content->arg);
		}

		/* Free the linked list of environment variables */
		if (content->env)
		{
			free_l_list(&(content->env));
		}

		/* Free the linked list of history entries */
		if (content->history)
		{
			free_l_list(&(content->history));
		}

		/* Free the linked list of aliases */
		if (content->alias)
			free_l_list(&(content->alias));

		/* Free the environ array and set it to NULL */
		multi_free(content->environ);
		content->environ = NULL;

		/* Free the cmd_buf array and set it to NULL */
		free_n_NULL((void **)content->cmd_buf);

		if (content->readfd > 2)
			close(content->readfd);

		_putchar(BUF_FLUSH);
	}
}
