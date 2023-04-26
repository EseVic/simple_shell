#include "shell.h"


/**
 * evaluate_command_chain - checks if a given command is part of a command chain (either an "AND" or "OR" chain), and modify a buffer accordingly based on the outcome of the evaluation
 * @content: struct parameter
 * @cmd_buffer: buffer's  char
 * @buffer_pos: command buffer's address of current position 
 * @cmd_index:  command buffer's starting position
 * @buffer_len: command buffer's length
 *
 * Return: nil
 */
void evaluate_command_chain(sh_args *content, char *cmd_buffer, size_t *buffer_pos, size_t cmd_index, size_t buffer_len)
{
	/* Get the length of the command buffer */
	buffer_len = strlen(cmd_buffer);

	/* Switch on the type of the command buffer */
  	switch (content->cmd_buf_type)
	{
    	case CMD_AND:
			/* If the command type is CMD_AND and the command status is true */
	    	/* set the last character of the command buffer to 0 and set the */
			/* buffer pointerto the end of the buffer */
      		if (content->status)
	  		{
				/* Set the last character of the command buffer to 0 */
        		cmd_buffer[cmd_index] = 0;
				/* Set the buffer pointer to the end of the buffer */
        		*buffer_pos = buffer_len;
      		}
      		break;
    	case CMD_OR:
			/* If the command type is CMD_OR and the command status is false */
      		/* set the last character of the command buffer to 0 and set the */
			/* buffer pointer to the end of the buffer */
      		if (!content->status)
	  		{
        		cmd_buffer[cmd_index] = 0;
				/* Set the buffer pointer to the end of the buffer */
        		*buffer_pos = buffer_len;
      		}
      		break;
  }
}


/**
 * detect_command_chaining - determines the type of command chaining as being a chain delimeter
 * @content: the parameter struct
 * @cmd_buffer: the char buffer
 * @buffer_pos: address of current position in cmd_buffer
 *
 * Return: 1 (chain delimeter), 0 (otherwise)
 */
int detect_command_chaining(sh_args *content, char *cmd_buffer, size_t *buffer_pos)
{
  	/* Get the current position in the buffer */
	size_t current_pos = *buffer_pos;

  	/* Check if the current character is a pipe (|) */
  	if (cmd_buffer[current_pos] == '|')
	{
    	/* Check if the next character is also a pipe (|) */
    	if (cmd_buffer[current_pos + 1] == '|')
		{
			/* Set the current position to the next character after the second pipe */
			cmd_buffer[current_pos] = 0;
			current_pos++;
      		/* If both characters are pipes, then this is an OR command */
      		content->cmd_buf_type = CMD_OR;
    	}
  	}
	else if (cmd_buffer[current_pos] == '&')
	{
    	/* Check if the next character is also an ampersand (&) */
    	if (cmd_buffer[current_pos + 1] == '&')
		{
			/* Set the current position to the next character after the second pipe */
			cmd_buffer[current_pos] = 0;
			current_pos++;
      		/* If both characters are ampersands, then this is an AND command */
      		content->cmd_buf_type = CMD_AND;

    	}
  	}
	else if (cmd_buffer[current_pos] == ';')
	{
		/* replace semicolon with null */
		cmd_buffer[current_pos] = 0;
    	/* If the current character is a semicolon, then this is the end of the command */
    	content->cmd_buf_type = CMD_CHAIN;
  	}
	else
	{
    	/* If the current character is not a pipe, ampersand, or semicolon, then this is not a command */
    	return (0);
  	}

  	/* Set the buffer pointer to the current position */
  	*buffer_pos = current_pos;

  	/* Return 1 to indicate that a command was found */
  	return (1);
}



/**
 * replaceStr_Contnt - replaces the content of a string with a new string
 * @oldStrPtr: the address to the old string
 * @newStr: the new string
 *
 * Return: 1 (string replaced)
 */
int replaceStr_Contnt(char **oldStrPtr, char *newStr)
{
	/* Free the old string */
	free(*oldStrPtr);

	/* Set the old string pointer to the new string */
	*oldStrPtr = newStr;
	return (1);
}


/**
 * replace_alias_with_value - replaces any aliases defined in the shell with their respective values
 * @content: struct parameter
 * Desc: It does this by searching for an alias with a prefix matching the first argument in the content struct, and if found, replacing it with the alias value
 *
 * Return: 1 (alias replaced), 0 (otherwise)
 */
int replace_alias_with_value(sh_args *content)
{
	char *alias_value;
	int count = 0;
	l_list *alias_node;
	

	while (count < 10)
	{
		/* Get the first node in the `content->alias` list that starts with */
		/* the value of `content->argv[0]` and is followed by an equal sign (=) */
		alias_node = get_first_node_with_prefix(content->alias, content->argv[0], '=');

		/* If no node was found, return 0 */
		if (!alias_node)
		{
			return (0);
		}

		free(content->argv[0]);

		/* Get the value of the alias */
		alias_value = car_finder(alias_node->str, '=');

		if (!alias_value)
		{
			return (0);
		}

		/* Create a new string that is the value of the alias, starting at the character after the equal sign (=) */
		alias_value = str_dup(alias_value + 1);

		if (!alias_value)
		{
			return (0);
		}
		content->argv[0] = alias_value;

		count++;
	}
	return (1);
}

/**
 * replace_var_values - replaces certain variables in the arguments passed to it with their corresponding values
 * @content: struct parameter
 * Desc: it replaces the following variables:
 * "$?" with the exit status of the most recently executed command.
 * "$$" with the process ID of the current shell process.
 * "${VAR}" with the value of the environment variable named VAR.
 *
 * Return: 1 (alias replaced), 0 (otherwise)
 */
int replace_var_values(sh_args *content)
{
	int arg_index = 0;
	l_list *env_var_node;

	for (arg_index = 0; content->argv[arg_index]; arg_index++)
	{
		/* If the current argument is not a variable, continue */
		if (!content->argv[arg_index][1] || content->argv[arg_index][0] != '$')
		{
			continue;
		}

		/* Check if the current argument is the special variable `$?` */
		if (!cmpare_strs(content->argv[arg_index], "$?"))
		{
			/* Replace the current argument with the value of the `content->status` variable */
			replaceStr_Contnt(&(content->argv[arg_index]),
				str_dup(custom_itoa(content->status, 10, 0)));
			continue;
		}

		/* Check if the current argument is the special variable `$$` */
		if (!cmpare_strs(content->argv[arg_index], "$$"))
		{
			/* Replace the current argument with the value of the `getpid()` function */
			replaceStr_Contnt(&(content->argv[arg_index]),
				str_dup(custom_itoa(getpid(), 10, 0)));
			continue;
		}

		/* Get the first node in the `content->env` list that starts with the value */
		/* of the current argument, followed by an equal sign (=) */
		env_var_node = get_first_node_with_prefix(content->env, &content->argv[arg_index][1], '=');

		if (env_var_node)
		{
			replaceStr_Contnt(&(content->argv[arg_index]),
				str_dup(car_finder(env_var_node->str, '=') + 1));
			continue;
		}

		/* Replace the current argument with the value of the environment variable */
		replaceStr_Contnt(&content->argv[arg_index], str_dup(""));

	}
	return (0);
}
