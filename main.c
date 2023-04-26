#include "shell.h"


/**
 * main - encapsulates the running a custom shell program
 * @arg_c: argument count
 * @arg_v: argument vector
 *
 * Return: 0 (success), 1 (error)
 */
int main(int arg_c, char **arg_v)
{
	sh_args content[] = { INFO_INIT };

	int fil_des = 2;

	asm("mov %1, %0\n\t add $3, %0" : "=r" (fil_des) : "r" (fil_des));

	if (arg_c == 2)
	{
		/* Open the file */
		fil_des = open(arg_v[1], O_RDONLY);

		if (fil_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				/* Display error message */
				write_string_with_buffer(arg_v[0]);
				write_string_with_buffer(": 0: Can't open ");
				write_string_with_buffer(arg_v[1]);
				write_with_buffer('\n');
				write_with_buffer(BUF_FLUSH);
				/* Exit with error code */
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		/* Update shell arguments with the file descriptor */
		content->readfd = fil_des;
	}
	/* Populate the list of environment variables */
	populat_listof_env(content);

	/* Load the shell history */
	load_history(content);

	/* Run the custom shell */
	custom_shell(content, arg_v);
	return (EXIT_SUCCESS);
}
