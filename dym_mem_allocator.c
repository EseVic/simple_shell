#include "shell.h"


/**
 * mem_alloc - resizes a previously allocated memory block
 * @prev_mem_size: byte size of previous block
 * @new_mem_size: byte size of new block
 * @first_ptr: pointer to previous malloc'ated block
 * Desc: It first calculates the minimum size between
 * the old size and the new size, and stores the result in old_size.
 * This is because we're only copying the minimum number of
 * bytes required to preserve the data in the memory block.
 * After which it copies over the data from the previously
 * allocated memory block to the new memory block. The loop
 * starts at old_size-1 and decrements old_size on each
 * iteration until it reaches 0. On each iteration, it copies
 * the byte at index "old_size" in the old memory block
 * to the same index in the new memory block.
 *
 * Return: pointer to newly allocated memory block (p)
 */
void *mem_alloc(void *first_ptr, unsigned int
prev_mem_size, unsigned int new_mem_size)
{
	char *new_ptr;

	if (!first_ptr)
		return (malloc(new_mem_size));

	/* deallocates "new size" if memory block is zero */
	if (!new_mem_size)
		return (free(first_ptr), NULL);

	/* if the new size of the memory block is equal to the old size. */
	/* If it is, then there's no need to resize the memory block */
	if (new_mem_size == prev_mem_size)
		return (first_ptr);

	new_ptr = malloc(new_mem_size);

	if (!new_ptr)
		return (NULL);

	prev_mem_size = prev_mem_size < new_mem_size ? prev_mem_size : new_mem_size;

	while (prev_mem_size--)
		new_ptr[prev_mem_size] = ((char *)first_ptr)[prev_mem_size];
	free(first_ptr);
	return (new_ptr);
}


/**
 * memset_clone - emulates "memset()"
 * function as it fills memory with a constant byte
 * @ptr: pointer to the memory area to be filled
 * @value: the value to be filled in the memory block
 * @num: the number of bytes to be set in the memory block
 *
 * Return: pointer to the memory area
 */
char *memset_clone(char *ptr, char value, unsigned int num)
{
	unsigned int x;

	for (x = 0; x < num; x++)
		ptr[x] = value;
	return (ptr);
}

/**
 * multi_free - frees memory allocated to a string of strings
 * @str_ptr: pointer to a string of strings
 */
void multi_free(char **str_ptr)
{
	char **my_strings = str_ptr;

	if (!str_ptr)
		return;
	while (*str_ptr)
		free(*str_ptr++);
	free(my_strings);
}


/**
 * free_n_NULL - free the memory pointed to by
 * @p: pointer address being freed
 *
 * Return: 1 (freed), 0 (otherwise)
 */
int free_n_NULL(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
