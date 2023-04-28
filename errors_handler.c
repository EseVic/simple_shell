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
	write_string_with_buffer(content->fname);
	write_string_with_buffer(": ");
	prnt_decim_int(content->line_count, STDERR_FILENO);
	write_string_with_buffer(": ");
	write_string_with_buffer(content->argv[0]);
	write_string_with_buffer(": ");
	write_string_with_buffer(err_str);
}
