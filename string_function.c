#include "shell.h"

/**
 * my_putstr - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t my_putstr(char *str)
{
	ssize_t number, lenght;

	number = str_len(str);
	lenght = write(STDOUT_FILENO, str, number);
	if (lenght != number)
	{
		perror("Error!");
		return (-1);
	}
	return (lenght);
}

/**
 * *str_dup - duplicates a string
 * @strdp: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *str_dup(char *strdp)
{
	char *copycat;

		int lenght, init;

	if (strdp == 0)
		return (NULL);

	for (lenght = 0; strdp[lenght]; lenght++)
		;
	copycat = malloc((lenght + 1) * sizeof(char));

	for (init = 0; init <= lenght; init++)
		copycat[init] = strdp[init];

	return (copycat);
}

/**
 * str_cmpr - compares two strings
 * @strcmp1: first string
 * @strcmp2: second string
 * Return: 0 on success, anything else is a failure
 */
int str_cmpr(char *strcmp1, char *strcmp2)
{
	int k;

	k = 0;
	while (strcmp1[k] == strcmp2[k])
	{
		if (strcmp1[k] == '\0')
			return (0);
		k++;
	}
	return (strcmp1[k] - strcmp2[k]);
}

/**
 * *str_cat - concatenates two strings
 * @strct1: first string
 * @strct2: second string
 * Return: pointer
 */
char *str_cat(char *strct1, char *strct2)
{
	char *newstr;
	unsigned int lenght1, lenght2, newlenght, i, j;

	lenght1 = 0;
	lenght2 = 0;
	if (strct1 == NULL)
		lenght1 = 0;
	else
	{
		for (lenght1 = 0; strct1[lenght1]; lenght1++)
			;
	}
	if (strct2 == NULL)
		lenght2 = 0;
	else
	{
		for (lenght2 = 0; strct2[lenght2]; lenght2++)
			;
	}
	newlenght = lenght1 + lenght2 + 2;
	newstr = malloc(newlenght * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	for (i = 0; i < lenght1; i++)
		newstr[i] = strct1[i];
	newstr[i] = '/';
	for (j = 0; j < lenght2; j++)
		newstr[i + 1 + j] = strct2[j];
	newstr[lenght1 + lenght2 + 1] = '\0';
	return (newstr);
}

/**
 * str_len - function to check lenght of string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int str_len(char *str)
{
	unsigned int lenght;

	lenght = 0;

	for (lenght = 0; str[lenght]; lenght++)
		;
	return (lenght);
}
