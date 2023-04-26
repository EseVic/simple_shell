#include "shell.h"


/**
 * print_err_mesg - The function writes an
 * error message to the standard error output
 * @content: struct parameter
 * @err_str: information about the source of the error
 *
 * Return: 0
 */
void print_err_mesg(sh_args *content, char *err_str)
{
	/* writes the filename to the buffer */
	write_string_with_buffer(content->fname);
	/* writes a colon and a space to the buffer */
	write_string_with_buffer(": ");
	/* writes the line number to the buffer */
	prnt_decim_int(content->line_count, STDERR_FILENO);
	write_string_with_buffer(": ");
	/* writes the command name to the buffer */
	write_string_with_buffer(content->argv[0]);
	write_string_with_buffer(": ");
	/* writes the error message to the buffer */
	write_string_with_buffer(err_str);
}
