#include "shell.h"

/**
 * custom_shell - custom shell implementation that reads
 * user input, interprets and executes commands
 * @content: struct parameter
 * @arg_v: argument vector
 *
 * Return: 0 (success), 1 (error)
 */
int custom_shell(sh_args *content, char **arg_v)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	/* Read input from the user, parse it, and execute commands until the user */
	/* requests to exit the shell or encounters an error */
	while (builtin_result != -2 && input_result != -1)
	{
		reset_sh_args(content);

		/* Print the shell prompt if the shell is in interactive mode */
		if (is_interactive(content))
		{
			_puts("$ ");
		}
		write_with_buffer(BUF_FLUSH);

		/* Read input from the user and process it */
		input_result = process_input(content);

		/* Fill the shell arguments struct with command-line arguments */
		if (input_result != -1)
		{
			fill_sh_args(content, arg_v);

			/* Search for and execute built-in commands */
			builtin_result = search_and_exec_builtin(content);
			/* If the command is not a built-in command, search for */
			/* and execute a system command */
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
	/* Exit the shell if the user requested to exit and the shell is in */
	/* interactive mode, or if a non-zero exit status was returned */
	if (builtin_result == -2)
	{
		if (content->err_num == -1)
		{
			exit(content->status);
		}
		exit(content->err_num);
	}

	/* Return the exit status of the last command executed */
	return (builtin_result);
}


/**
 * findAndExecCommand - function finds the path to an executable file
 * based on the command-line arguments and then calls fork_cmd to execute the file
 * @content: struct parameter
 *
 * Return: nil
 */
void findAndExecCommand(sh_args *content)
{
	char *path = NULL;
	int index = 0;
	int non_delim_count = 0;

	/* Set path and increase line count if necessary */
	content->path = content->argv[0];
	if (content->linecount_flag == 1)
	{
	content->line_count++;
	content->linecount_flag = 0;
	}

	/* Count number of non-delimiter arguments */
	while (content->arg[index])
	{
	if (!is_delimiter(content->arg[index], " \t\n"))
		non_delim_count++;
		index++;
	}

	/* Return if no non-delimiter arguments */
	if (!non_delim_count)
	{
	return;
	}

	/* Find the executable path */
	path = find_exec_path(content, getenv_clone(content, "PATH="), content->argv[0]);

	/* Execute the command if path exists */
	if (path)
	{
	content->path = path;
	custom_fork(content);
	return;
	}

	/* Check if the file is executable */
	if ((is_interactive(content) 
		|| getenv_clone(content, "PATH=")
		|| content->argv[0][0] == '/') 
		&& is_file_exec(content, content->argv[0]))
	{
	custom_fork(content);
	return;
	}

	/* Handle error case */
	if (*(content->arg) != '\n')
	{
	content->status = 127;
	print_err_mesg(content, "not found\n");
	}
}


/**
 * custom_fork - forks a system call to create a new process
 * @content: struct parameter
 *
 * Return: nil
 */
void custom_fork(sh_args *content)
{
	int execve_status, wait_status;

	/* Fork the current process and check for errors */
	pid_t child_pid = fork();
	if (child_pid == -1)
	{
	perror("fork");
	return;
	}

	/* If this is the child process, execute the desired program */
	if (child_pid == 0)
	{
		/* Execute the program using the arguments provided by the user */
	execve_status = execve(content->path, content->argv, environ_getter(content));
	perror("execve");
	free_sh_args(content, 1);
	exit(execve_status == -1 ? 1 : 0);
	}
	else
	{
		/* If this is the parent process, wait for the child process to exit */
		waitpid(child_pid, &wait_status, 0);
		/* If the child process exited normally, store its exit status in the content struct */
		if (WIFEXITED(wait_status))
		{
			content->status = WEXITSTATUS(wait_status);
		if (content->status == 126)
		{
			print_err_mesg(content, "Permission denied\n");
		}
		}
		else
		{
			/* If waitpid() failed, store an error status in the content struct and print an error message */
			content->status = 1;
			perror("waitpid");
		}
	}
}


/**
 * search_and_exec_builtin - searches for a built-in command in a shell program
 * @content: struct parameter
 *
 * Return: -1 (builtin is not found), 0 (builtin is executed),
 * 1 (builtin found but not executed),-2 (builtin signals exit())
 */
int search_and_exec_builtin(sh_args *content)
{
	int builtin_return = -1;
	int idx = 0;

	/* list of built-in commands */
	builtin_table builtin_table_list[] = {
		{"exit", shell_exit},
		{"env", env_clone},
		{"help", help_command},
		{"history", print_command_hist},
		{"setenv", check_env_setter},
		{"unsetenv", check_env_unsetenv},
		{"cd", change_directory},
		{"alias", alias_clone},
		{NULL, NULL}
	};

	/* Loop through the list of built-in commands */
	while (builtin_table_list[idx].type != NULL)
	{
		/* If the first argument matches a built-in command,*/
		/* execute it and set the return value */
		if (cmpare_strs(content->argv[0], builtin_table_list[idx].type) == 0)
		{
			content->line_count++;
			builtin_return = builtin_table_list[idx].func(content);
			break;
		}
		idx++;
	}

	/* Return the return value of the executed*/
	/*command or -1 if no command was found */
	return (builtin_return);
}
