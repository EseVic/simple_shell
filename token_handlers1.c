#include "shell.h"


/**
 * evaluate_command_chain - checks if a given command is part of a
 *	command chain (either an "AND" or "OR" chain), and modify a
 *	buffer accordingly based on the outcome of the evaluation
 * @content: struct parameter
 * @cmd_buffer: buffer's  char
 * @buffer_pos: command buffer's address of current position
 * @cmd_index:  command buffer's starting position
 * @buffer_len: command buffer's length
 *
 * Return: nil
 */
void evaluate_command_chain(sh_args *content, char *cmd_buffer,
		size_t *buffer_pos, size_t cmd_index, size_t buffer_len)
{
	size_t current_pos = *buffer_pos;

	if (content->cmd_buf_type == CMD_AND)
	{
		if (content->status)
		{
			cmd_buffer[cmd_index] = 0;
			current_pos = buffer_len;
		}
	}
	if (content->cmd_buf_type == CMD_OR)
	{
		if (!content->status)
		{
			cmd_buffer[cmd_index] = 0;
			current_pos = buffer_len;
		}
	}

	*buffer_pos = current_pos;
}


/**
 * detect_command_chaining - determines the type of command chaining
 *	as being a chain delimeter
 * @content: the parameter struct
 * @cmd_buffer: the char buffer
 * @buffer_pos: address of current position in cmd_buffer
 *
 * Return: 1 (chain delimeter), 0 (otherwise)
 */
int detect_command_chaining(sh_args *content, char *cmd_buffer,
		size_t *buffer_pos)
{
	size_t current_pos = *buffer_pos;

	if (cmd_buffer[current_pos] == '|' && cmd_buffer[current_pos + 1] == '|')
	{
		cmd_buffer[current_pos] = 0;
		current_pos++;
		content->cmd_buf_type = CMD_OR;
	}
	else if (cmd_buffer[current_pos] == '&' && cmd_buffer[current_pos + 1] == '&')
	{
		cmd_buffer[current_pos] = 0;
		current_pos++;
		content->cmd_buf_type = CMD_AND;
	}
	else if (cmd_buffer[current_pos] == ';') /* found end of this command */
	{
		cmd_buffer[current_pos] = 0; /* replace semicolon with null */
		content->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*buffer_pos = current_pos;
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
	free(*oldStrPtr);
	*oldStrPtr = newStr;
	return (1);
}


/**
 * replace_alias_with_value - replaces any aliases defined in the
 *	shell with their respective values
 * @content: struct parameter
 * Desc: It does this by searching for an alias with a prefix matching
 *	the first argument in the content struct, and if found,
 *	replacing it with the alias value
 *
 * Return: 1 (alias replaced), 0 (otherwise)
 */
int replace_alias_with_value(sh_args *content)
{
	int count;
	l_list *alias_node;
	char *alias_value;

	for (count = 0; count < 10; count++)
	{
		alias_node = get_first_node_with_prefix(content->alias,
				content->argv[0], '=');
		if (!alias_node)
			return (0);
		free(content->argv[0]);
		alias_value = car_finder(alias_node->str, '=');
		if (!alias_value)
			return (0);
		alias_value = str_dup(alias_value + 1);
		if (!alias_value)
			return (0);
		content->argv[0] = alias_value;
	}
	return (1);
}

/**
 * replace_var_values - replaces certain variables in the arguments
 *	passed to it with their corresponding values
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
		if (content->argv[arg_index][0] != '$' || !content->argv[arg_index][1])
			continue;

		if (!cmpare_strs(content->argv[arg_index], "$?"))
		{
			replaceStr_Contnt(&(content->argv[arg_index]),
				str_dup(custom_itoa(content->status, 10, 0)));
			continue;
		}
		if (!cmpare_strs(content->argv[arg_index], "$$"))
		{
			replaceStr_Contnt(&(content->argv[arg_index]),
				str_dup(custom_itoa(getpid(), 10, 0)));
			continue;
		}
		env_var_node = get_first_node_with_prefix(content->env,
				&content->argv[arg_index][1], '=');
		if (env_var_node)
		{
			replaceStr_Contnt(&(content->argv[arg_index]),
				str_dup(car_finder(env_var_node->str, '=') + 1));
			continue;
		}
		replaceStr_Contnt(&content->argv[arg_index], str_dup(""));

	}
	return (0);
}
