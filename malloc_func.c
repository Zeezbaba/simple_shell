#include "shell.h"

/**
 * **mem_realloc - function to reallocates a pointer
 * @ptr: old array pointer
 * @mem: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **mem_realloc(char **ptr, size_t *mem)
{
	char **status;
	size_t j;

	status = malloc(sizeof(char *) * ((*mem) + 10));
	if (status == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (j = 0; j < (*mem); j++)
	{
		status[j] = ptr[j];
	}
	*mem += 10;
	free(ptr);
	return (status);
}
