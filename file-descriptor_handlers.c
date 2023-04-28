#include "shell.h"


/**
 * write_string_to_fd - write the string to a stream
 * @str: string being printed
 * @fil_des: filedescriptor written to
 *
 * Return: characters written
 */
int write_string_to_fd(char *str, int fil_des)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += write_car_to_fd(*str++, fil_des);
	}
	return (count);
}

/**
 * write_car_to_fd - writes characters
 * to a file descriptor fil_des in a buffered manner
 * @car: character being printed
 * @fil_des: filedescriptor written to
 *
 * Return: 1 (success), -1 (error)
 */
int write_car_to_fd(int fil_des, char car)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (car == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fil_des, buffer, index);
		index = 0;
	}
	if (car != BUF_FLUSH)
		buffer[index++] = car;
	return (1);
}


/**
 * prnt_decim_int - print the value of the
 * "feed" argument as a decimal number i.e base 10
 * @feed: the input
 * @fil_des: the filedescriptor to write to
 * Desc: If the "feed" argument is negative, the function
 * calculates the absolute value of "feed3" and sets avariable
 * named "absol_val" to that value. It then prints a minus sign
 * to indicate that the number is negative,and increments the
 * "count" variable to reflect the fact that an additional
 * character was printed, then if non-negative, the function
 * simply sets "absol_val" equal to "feed". To print it initializes
 * "remaining" to "absol_val", and then using a loop to iterate
 * through the powers of 10, starting with 1000000000 and dividing
 * by 10 each time. For each power of 10, the function checks if
 * "absol_val" is divisible by that power of 10 If it is, it prints
 * the corresponding digit of "remaining" divided by that power
 * of 10 (using the ASCII code for the digit), and increments
 * the "count" variable. It then updates "remaining" to be equal
 * to the remainder of "absol_val" divided by that power of 10.
 * Then function prints the last digit of "remaining" also
 * using the ASCII code and increments "count" one final time.
 * It then returns the value of "count",
 * indicating how many characters were printed
 *
 * Return: printed characters
 */
int prnt_decim_int(int feed, int fil_des)
{
	int (*_puchar)(char) = _putchar;
	int index, count = 0;
	unsigned int absol_val, remaining;

	/* _puchar writes to stderr*/
	if (fil_des == STDERR_FILENO)
		_puchar = write_with_buffer;

	if (feed < 0)
	{
		absol_val = -feed;
		_puchar('-');
		count++;
	}
	else
		absol_val = feed;
	remaining = absol_val;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absol_val / index)
		{
			_puchar('0' + remaining / index);
			count++;
		}
		remaining %= index;
	}
	_puchar('0' + remaining);
	count++;

	return (count);
}
