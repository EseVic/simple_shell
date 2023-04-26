#include "shell.h"


/**
 * evaluate_command - evaluates a single command in a chain of commands
 *	by processing the command's arguments and storing them in a buffer
 * @content: struct parameter
 * @command_chain_buffer: holds a buffer of command chains,
 *	which are sequences of
 *	commands separated by command chaining characters
 * @next_position:  keep track of the next position
 *	in the command_chain_buffer that
 *	needs to be evaluated by the evaluate_command() function
 * @current_position: keep track of the current position in
 *	the command_chain_buffer
 *	that is being evaluated by the evaluate_command() function
 * @buffer_length: keep track of the length of the
 *	command_chain_buffer that is being
 *	evaluated by the evaluate_command() function
 *
 * Return: nil
 */
void evaluate_command(sh_args *content, char *command_chain_buffer,
		size_t *next_position, size_t current_position,
		size_t buffer_length)
{
	char **current_command_pointer = &(content->arg), *current_command;

	current_command = command_chain_buffer + current_position;
	evaluate_command_chain(content, command_chain_buffer,
			next_position, current_position, buffer_length);
	for ( ; *next_position < buffer_length; (*next_position)++)
	{
		if (detect_command_chaining(content, command_chain_buffer, next_position))
			break;
	}
	/* update the current position to the next position, and reset the buffer */
	/* length and command buffer type if necessary */
	current_position = *next_position + 1;
	if (current_position >= buffer_length)
	{
		current_position = buffer_length = 0;
		content->cmd_buf_type = CMD_NORM;
	}
	*current_command_pointer = current_command;
}


/**
 * process_input - reads user input from the command line
 *	(apart from the newline)
 * @content: struct parameter
 *
 * Return: length of the current command
 */
ssize_t process_input(sh_args *content)
{
	static char *command_chain_buffer;
	static size_t buffer_length;
	static size_t current_position;
	static size_t next_position;
	ssize_t input_length = 0;

	/* clear the buffer before processing new input */
	_putchar(BUF_FLUSH);

	/* read input from stdin and store it in the buffer */
	input_length = get_input_from_stdin(content,
			&command_chain_buffer, &buffer_length);

	/* return -1 if EOF is reached */
	if (input_length == -1)
		return (-1);

	if (buffer_length)
	{
		next_position = current_position;
		evaluate_command(content, command_chain_buffer,
				&next_position, current_position,
				buffer_length);

		for ( ; next_position < buffer_length; next_position++)
			evaluate_command(content, command_chain_buffer,
			&next_position, current_position, buffer_length);

		/* reset the buffer length and command buffer type */
		current_position = buffer_length = 0;
		content->cmd_buf_type = CMD_NORM;

		/* return the length of the command chain buffer */
		return (len_of_str(command_chain_buffer));
	}
	else
	{
		content->arg = command_chain_buffer;
		return (input_length);
	}
}


/**
 * read_into_buffer - reads data from a file descriptor into a buffer,
 *	up to a maximum size specified by READ_BUF_SIZE
 * @content: struct parameter
 * @buffer: buffer
 * @bytes_read: size
 *
 * Return: result, error
 */
ssize_t read_into_buffer(sh_args *content,
		char *buffer, size_t *bytes_read)
{
	ssize_t result = 0;

	if (*bytes_read != 0)
		return (0);

	/* Attempt to read from the file descriptor into the buffer */
	result = read(content->readfd, buffer, READ_BUF_SIZE);

	/* If the read succeeded, update the bytes_read variable */
	if (result >= 0)
	{
		*bytes_read = result;
	}

	return (result);
}


/**
 * get_input_from_stdin - reads input from standard input (stdin)
 *	and store it in a buffer
 * @content: parameter struct
 * @input_buffer: buffer's address
 * @buffer_size: buffer_size  address
 * Desc: If there is no input left in the buffer, the function
 *	will fill the buffer by calling getline or read_input_line
 *	function to read input from stdin. The input is then
 *	processed by removing any trailing newline, removing
 *	comments, adding it to the command history, and
 *	determining if it is a command chain by checking for
 *	the presence of a semicolon
 *
 * Return: number of characters read
 */
ssize_t get_input_from_stdin(sh_args *content, char **input_buffer,
		size_t *buffer_size)
{
	ssize_t read_len = 0;
	size_t allocated_bufferLen = 0;

	if (*buffer_size == 0)
	{
		free(*input_buffer);
		*input_buffer = NULL;

		/* Set signal handler for SIGINT */
		signal(SIGINT, handle_sigInt);

		/* Use getline to read input from stdin, and store it in the input buffer */
		#if USE_GETLINE
		read_len = getline(input_buffer, &allocated_bufferLen, stdin);
		#else
		/* Otherwise, read input character by character using read_input_line() */
		read_len = read_input_line(content, input_buffer, &allocated_bufferLen);
		#endif

		if (read_len > 0)
		{
			if ((*input_buffer)[read_len - 1] == '\n')
			{
				(*input_buffer)[read_len - 1] = '\0';
				read_len--;
			}
			content->linecount_flag = 1;
			coments_remover(*input_buffer);
			add_to_history(content, *input_buffer, content->histcount++);

			/* Update buffer size and command buffer pointer */
			{
				*buffer_size = read_len;
				content->cmd_buf = input_buffer;
			}
		}
	}
	return (read_len);
}


/**
 * read_input_line - reads input from file and store it in a char array
 * @content: parameter struct
 * @ptr: stores pointer that will point to the output buffer
 * @length: stores the length of the line that was read and '\0'
 *
 * Return: total_bytes
 */
int read_input_line(sh_args *content, char **ptr, size_t *length)
{
	char *input_pos, *new_output_str  = NULL, *line_end;
	static char input_buf[READ_BUF_SIZE];
	static size_t buf_pos, buf_len;
	size_t line_len;
	ssize_t bytes_read, total_bytes = 0;

	input_pos = *ptr;

	if (length && input_pos)
		total_bytes = *length;
	if (buf_pos == buf_len)
		buf_pos = buf_len = 0;

	bytes_read = read_into_buffer(content, input_buf, &buf_len);
	if (bytes_read == -1 || (bytes_read == 0 && buf_len == 0))
		return (-1);

	line_end = car_finder(input_buf + buf_pos, '\n');

	line_len = line_end ? 1 + (unsigned int)(line_end - input_buf) : buf_len;
	new_output_str = mem_alloc(input_pos,
			total_bytes, total_bytes ? total_bytes + line_len : line_len + 1);

	if (!new_output_str)
		return (input_pos ? free(input_pos), -1 : -1);
	if (total_bytes)
		string_concat(new_output_str, input_buf + buf_pos, line_len - buf_pos);
	else
		cpy_str(new_output_str, input_buf + buf_pos, line_len - buf_pos + 1);

	total_bytes += line_len - buf_pos;
	buf_pos = line_len;
	input_pos = new_output_str;

	if (length)
		*length = total_bytes;

	*ptr = input_pos;
	return (total_bytes);
}



