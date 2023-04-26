#include "shell.h"


/**
 * change_directory - changes the curren
 *  working directory of the shell
 * @content: struct parameter
 * Desc: getcwd gets the current working directory and
 * stores it in the buffer. If it is empty, it sets the dir
 * variable to the value of the HOME environment variable,
 * and if that fails, it sets dir to the value of the PWD
 * environment variable. It then calls the chdir function to
 * change the current working directory to the value of dir.
 * If the first argument is not empty, the function checks if
 * it is equal to "-". If it is, it prints the current working
 * directory to standard output and sets the dir variable to the
 * value of the OLDPWD. If the first argument is not empty and
 * not equal to "-", the function simply calls chdir to change
 * the current working directory to the value of the first argument.
 * Then it sets OLDPWD and PWD to the shell's environment variable table
 *
 * Return: 0 (success), 1 (error)
 */
int change_directory(sh_args *content)
{
	const int buf_size = 1024;
	int cd_success;
	char *buff = malloc(buf_size * sizeof(char));
	char *dir = NULL;
	char *wrkin_dir = getcwd(buff, buf_size);
	char *err_msg = NULL;

	if (!buff)
	{
		_puts("Error: could not allocate memory\n");
		return (1);
	}

	 /* gets the current working directory */
	if (!wrkin_dir)
	{
	/* handles getcwd failure */
	err_msg = strerror(errno);
	_puts("Error: ");
	_puts(err_msg);
	_putchar('\n');
	return (1);
	}

	/* determines the directory to change to based on the arguments */
	if (!content->argv[1])
	{
	/* If no directory is specified, change to the user's home directory */
	dir = getenv_clone(content, "HOME=");
	if (!dir)
	{
		dir = getenv_clone(content, "PWD=");
	}
	}
	else if (cmpare_strs(content->argv[1], "-") == 0)
	{
	/* If the argument is '-', change to the previous working directory */
	dir = getenv_clone(content, "OLDPWD=");
	if (!dir)
	{
		_puts(wrkin_dir);
		_putchar('\n');
		return (1);
	}
	_puts(dir);
	_putchar('\n');
	}
	else
	{
		dir = content->argv[1];
	}

	cd_success = chdir(dir);
	if (cd_success == -1)
	{
		print_err_mesg(content, "can't cd to ");
		write_with_buffer('\n');
	}
	else
	{
		env_setter(content, "OLDPWD", getenv_clone(content, "PWD="));
		env_setter(content, "PWD", getcwd(buff, buf_size));
	}

	free(buff);
	return (0);
}
/**
 * help_command -  to provide a placeholder
 * for the "help" command in a shell program
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
		_puts("\tChange the current directory to DIR.  The default DIR is the value of the\n");
		_puts("\tHOME shell variable.\n\n");
		_puts("\tThe variable CDPATH defines the search path for the directory containing\n");
		_puts("\tDIR.  Alternative directory names in CDPATH are separated by a colon (:).\n");
		_puts("\tA null directory name is the same as the current directory.  If DIR begins\n");
		_puts("\twith a slash (/), then CDPATH is not used.\n\n");
		_puts("\tExit Status:\n");
		_puts("\tReturns 0 if the directory is changed,
			and if $PWD is set successfully when\n");
		_puts("\t-P is used; non-zero otherwise.\n");



	_puts("\n");
	_puts("\t\n");
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
	if (content->argv[1] == NULL) {
	content->err_num = -1;
	return (-2);
	}

	/* converts exit argument to an integer */
	exit_status = exit_str_to_int(content->argv[1]);

	/* If the exit argument is not a valid integer, print an error message */
	if (exit_status == -1) {
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
 * input string is a + sign. If it is, it increments the pointer
 * (str++) to move past the + sign. whether each character is a digit
 * between 0 and 9. If it is, it multiplies the converted_output by 10
 * and adds the value of the current digit to it. If the converted_output
 * exceeds the maximum value of an integer (INT_MAX),
 * the function returns -1 indicating an error
 *
 * Return: 0 , -1 (error, if the input string
 * contains non-numeric characters)
 */
int exit_str_to_int(char *str)
{
	int count = 0;
	unsigned long int converted_output = 0;
	bool is_negative = false;

	/* checks for number polarity */
	if (*str == '+')
	{
		str++;
	}
	else if (*str == '-')
	{
		is_negative = true;
		str++;
	}

	/* Iterates through the string and convert each digit to integer */
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

	/* checks if the number is negative and within the range of INT_MIN */
	if (is_negative)
	{
	if (converted_output > (unsigned long)INT_MAX + 1)
	{
		return (-1);
        }
	return (-((int)converted_output));
	}
	else
	{
		if (converted_output > INT_MAX)
		return (-1);

	return ((int)converted_output);
	}
}
