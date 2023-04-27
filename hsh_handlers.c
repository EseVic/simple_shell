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
	char *ptr = str;

	if (str == NULL)
	{
	return (0);
	}

	/* Write the current character to the file descriptor, */
	/* and add the number of characters written to the count */
	for ( ; *ptr != '\0'; ptr++)
	count += write_car_to_fd(*ptr, fil_des);

	return (count);
}

/**
 * write_car_to_fd - writes characters to a
 * file descriptor fil_des in a buffered manner
 * @car: character being printed
 * @fil_des: filedescriptor written to
 *
 * Return: 1 (success), -1 (error)
 */
int write_car_to_fd(int fil_des, char car)
{
	static char buffer[WRITE_BUF_SIZE];
	static int index;

	/* If the character is the BUF_FLUSH character or the buffer is full, */
	/* write the contents of the buffer to*/
	/*the file descriptor and reset the index */
	if (index >= WRITE_BUF_SIZE || car == BUF_FLUSH)
	{
		write(fil_des, buffer, index);
		index = 0;
	}

	if (car != BUF_FLUSH)
	{
		buffer[index++] = car;
	}

	return (1);
}


/**
 * prnt_decim_int - print the value of the "feed"
 * argument as a decimal number i.e base 10
 * @feed: the input
 * @fil_des: the filedescriptor to write to
 * Desc: If the "feed" argument is negative, the function calculates
 * the absolute value of "feed3" and sets a variable named "absol_val"
 * to that value. It then prints a minus sign to indicate that th number
 * is negative, and increments the "count" variable to reflect the fact
 * that an additional character was printed, then if non-negative, the
 * function simply sets "absol_val" equal to "feed". To print it
 * initializes "remaining" to "absol_val", and then using a loop to
 * iterate through the powers of 10, starting with 1000000000 and dividing
 * by 10 each time. For each power of 10, the function checks if "absol_val"
 * is divisible by that power of 10. If it is, it prints the corresponding
 * digit of "remaining" divided by that power of 10 (using the ASCII code
 * for the digit), and increments the "count" variable. It then updates
 * "remaining" to be equal to the remainder of "absol_val" divided by
 * that power of 10. Then function prints the last digit of "remain"
 * also using the ASCII code and increments "count" one final time.
 * It then returns the value of "count",
 *indicating how many characters were printed
 *
 * Return: printed characters
 */
int prnt_decim_int(int feed, int fil_des)
{
	int count = 0;
	int (*output)(char) = _putchar;

	/* If the file descriptor is standard error,*/
	/*use the buffered output function instead */
	if (fil_des == STDERR_FILENO)
	{
		output = write_with_buffer;
	}

	/* If the number is negative, print a '-' sign and negate the number */
	if (feed < 0)
	{
		output('-');
		count++;
		feed = -feed;
	}

	/* If the number has more than one digit,*/
	/*print the leftmost digits recursively */
	if (feed >= 10)
	count += prnt_decim_int(feed / 10, fil_des);

	/* Print the last digit */
	output('0' + feed % 10);
	count++;

	/* Return the total number of characters printed */
	return (count);
}
