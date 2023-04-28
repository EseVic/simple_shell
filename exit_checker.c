#include "shell.h"


/**
 * change_directory - changes the current
 * working directory of the shell
 * @content: struct parameter
 * Desc: getcwd gets the current working directory and
 * stores it in the buffer. If it is empty, it sets
 * the dir variable to the value of the HOME environment
 * variable, and if that fails, it sets dir to the
 * value of the PWD environment variable. It then calls
 * the chdir function to change the current working
 * directory to the value of dir. If the first argument
 * is not empty, the function checks if it is equal to "-".
 * If it is, it prints the current working directory
 * to standard output and sets the dir variable to the value
 * of the OLDPWD. If the first argument is not empty
 * and not equal to "-", the function simply calls chdir to
 * change the current working directory to the value of
 * the first argument. Then it sets OLDPWD and PWD to the
 * shell's environment variable table
 *
 * Return: 0 (success), 1 (error)
 */
int change_directory(sh_args *content)
{
	int cd_success;
	char buff[1024], *wrkin_dir, *dir;

	wrkin_dir = getcwd(buff, 1024);
	if (wrkin_dir == NULL)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!content->argv[1])
	{
		dir = getenv_clone(content, "HOME=");
		if (dir == NULL)
			cd_success = chdir((dir = getenv_clone(content, "PWD=")) ? dir : "/");
		else
			cd_success = chdir(dir);
	}
	else if (cmpare_strs(content->argv[1], "-") == 0)
	{
		if (!getenv_clone(content, "OLDPWD="))
		{
			_puts(wrkin_dir);
			_putchar('\n');
			return (1);
		}
		_puts(getenv_clone(content, "OLDPWD=")), _putchar('\n');
		cd_success = chdir((dir = getenv_clone(content, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_success = chdir(content->argv[1]);
	if (cd_success == -1)
	{
		print_err_mesg(content, "can't cd to ");
		write_string_with_buffer(content->argv[1]), write_with_buffer('\n');
	}
	else
	{
		env_setter(content, "OLDPWD", getenv_clone(content, "PWD="));
		env_setter(content, "PWD", getcwd(buff, 1024));
	}
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

	/* If no argument is provided, show general help message */
	_puts("Welcome to the Shell Help Menu:\n   help: Show this help menu\n");
	_puts("   cd: Change directory\n   exit: Exit the shell\n");

	if (0)
	{
		_puts(*arg_v);
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
	int exitcheck;

	if (content->argv[1])
	{
		/* converts exit argument to an integer */
		exitcheck = exit_str_to_int(content->argv[1]);

		/* If the exit arg is not a valid integer, print an err mesg */
		if (exitcheck == -1)
		{
			content->status = 2;
			print_err_mesg(content, "Error number: ");
			write_string_with_buffer(content->argv[1]);
			write_with_buffer('\n');
			return (1);
		}
		content->err_num = exit_str_to_int(content->argv[1]);
		return (-2);
	}
	content->err_num = -1;
	return (-2);
}


/**
 * exit_str_to_int - converts string inputs to integer
 * @str: string being converted
 * Desc: It then checks whether the first character
 * of the input string is a + sign. If it is, it increments
 * the pointer (str++) to move past the + sign. whether each
 * character is a digit between 0 and 9. If it is, it
 * multiplies the converted_output by 10 and adds the
 * value of the current digit to it. If the converted_output
 * exceeds the maximum value of an integer (INT_MAX),
 * the function returns -1 indicating an error
 *
 * Return: 0 , -1 (error, if the input string contains non-numeric characters)
 */
int exit_str_to_int(char *str)
{
	unsigned long int converted_output = 0;
	int count = 0;

	/* checks for number polarity */
	if (*str == '+')
	{
		str++;
	}

	/* Iterates through the string and convert each digit to integer */
	for (count = 0;  str[count] != '\0'; count++)
	{
		if (str[count] <= '9' && str[count] >= '0')
		{
			converted_output *= 10;
			converted_output += (str[count] - '0');
			if (converted_output > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}

	}
	return (converted_output);
}
