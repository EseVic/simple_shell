#include "shell.h"


/**
 * help_command -  to provide a placeholder
 *	for the "help" command in a shell program
 * @content: struct parameter
 *
 * Return: 0
 */
int help_command(sh_args *content)
{
	char **arg_v = content->argv;

	if (arg_v[1] == NULL)
	{
		/* If no argument is provided, show general help message */
		_puts("Welcome to the Shell Help Menu:\n   help: Show this help menu\n");
		_puts("   cd: Change directory\n   exit: Exit the shell\n");
	}
	else
	{
		/* If an argument is provided, show specific help message for that command */
		if (strcmp(arg_v[1], "cd") == 0)
		{
			_puts("cd: cd\n");
			_puts("\tChange the shell working directory.\n\n");
			_puts("\tExit Status:\n");
			_puts("\tReturns 0 if the directory is changed,
			and if $PWD is set successfully when\n");
		}
		else if (strcmp(arg_v[1], "help") == 0)
		{
			_puts("help - Show help menu\n");
			_puts("Usage: help [COMMAND]\n");
			_puts("Shows help for the specified command,
				or general help if no command is specified.\n");
		}
		else if (strcmp(arg_v[1], "exit") == 0)
		{
			_puts("exit - Exit the shell\n");
			_puts("Usage: exit\n");
			_puts("Exits the shell.\n");
		}
		else
		{
			_puts("Command not found. Type 'help' for a list of available commands.\n");
		}
	}
	return (0);
}


/**
 * shell_exit - terminates the shell's working process
 * @content: struct parameter
 *
 * Return: 0
 */
int shell_exit(sh_args *content)
{
	int exit_status;

	/* checks if there is an exit argument */
	if (content->argv[1] == NULL)
	{
		content->err_num = -1;
		return (-2);
	}

	/* converts exit argument to an integer */
	exit_status = exit_str_to_int(content->argv[1]);
	/* If the exit argument is not a valid integer, print an error message */
	if (exit_status == -1)
	{
		content->status = 2;
		print_err_mesg(content, "Illegal number: ");
		write_string_with_buffer(content->argv[1]);
		write_with_buffer('\n');
		return (1);
	}

	content->err_num = exit_status;
	return (-2);
}


/**
 * exit_str_to_int - converts string inputs to integer
 * @str: string being converted
 * Desc: It then checks whether the first character of the
 *	input string is a + sign. If it is, it increments the pointer
 *	(str++) to move past the + sign. whether each character is a digit
 *	between 0 and 9. If it is, it multiplies the converted_output by 10
 *	and adds the value of the current digit to it. If the converted_output
 *	exceeds the maximum value of an integer (INT_MAX),
 *	the function returns -1 indicating an error
 *
 * Return: 0 , -1 (error, if the input string
 *	contains non-numeric characters)
 */
int exit_str_to_int(char *str)
{
	int count = 0;
	unsigned long int converted_output = 0;
	bool is_negative = false;

	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		is_negative = true;
		str++;
	}
	while (str[count] != '\0')
	{
		if (str[count] >= '0' && str[count] <= '9')
		{
			converted_output *= 10;
			converted_output += (str[count] - '0');
			if (converted_output > INT_MAX)
			{
				return (-1);
			}
		}
		else
			return (-1);
		count++;
	}
	if (is_negative)
	{
		if (converted_output > (unsigned long)INT_MAX + 1)
			return (-1);
		return (-((int)converted_output));
	}
	else
	{
		if (converted_output > INT_MAX)
			return (-1);
		return ((int)converted_output);
	}
}
