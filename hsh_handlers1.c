#include "shell.h"


/**
 * execute_shell - function to execute the custom shell
 * @content: struct parameter
 * @arg_v: argument vector
 *
 * Return: builtin_result (success)
 */
int execute_shell(sh_args *content, char **arg_v)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (builtin_result != -2 && input_result != -1)
	{
		reset_sh_args(content);

		if (is_interactive(content))
		{
			_puts("$ ");
		}
		write_with_buffer(BUF_FLUSH);

		input_result = process_input(content);

		if (input_result != -1)
		{
			fill_sh_args(content, arg_v);

			builtin_result = search_and_exec_builtin(content);

			if (builtin_result == -1)
			{
				findAndExecCommand(content);
			}
		}
		else if (is_interactive(content))
		{
			_putchar('\n');
		}
		free_sh_args(content, 0);
	}
	write_shel_histry(content);
	free_sh_args(content, 1);
	if (!is_interactive(content) && content->status)
	{
		exit(content->status);
	}

	return (builtin_result);
}


/**
 * countNonDelimiterArgs - function to count non delimiter arguments
 * @arg: arument parameter
 *
 * Return: non_delim_count (success)
 */

int countNonDelimiterArgs(char **arg)
{
	int index = 0;
	int non_delim_count = 0;

	while (arg[index])
	{
		if (!is_delimiter(arg[index], " \t\n"))
			non_delim_count++;
		index++;
	}

	return (non_delim_count);
}
