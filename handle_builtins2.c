#include "shell.h"

/**
 * add_keys - add new variable
 * @vars: pointer to struct of variables
 *
 * Return: nothing
 */
void add_keys(vars_t *vars)
{
	unsigned int i;
	char **environs;

	for (i = 0; vars->env[i] != NULL; i++)
		;
	environs = malloc(sizeof(char *) * (i + 2));
	if (environs == NULL)
	{
		std_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != NULL; i++)
		environs[i] = vars->env[i];
	environs[i] = add_value(vars->av[1], vars->av[2]);
	if (environs[i] == NULL)
	{
		std_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		rel_env_mode(vars->env);
		free(environs);
		exit(127);
	}
	environs[i + 1] = NULL;
	free(vars->env);
	vars->env = environs;
}

/**
 * env_func - function to locate a variable
 * @env: array of environment variables
 * @key: seached variable
 *
 * Return: pointer to address of the environment variable
 */
char **env_func(char **env, char *key)
{
	unsigned int init, n, lenght;

	lenght = str_len(key);
	for (init = 0; env[init] != NULL; init++)
	{
		for (n = 0; n < lenght; n++)
			if (key[n] != env[init][n])
				break;
		if (n == lenght && env[init][n] == '=')
			return (&env[init]);
	}
	return (NULL);
}

/**
 * add_value - add new variable string
 * @key: variable name
 * @value: value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int lenght1, lenght2, i, j;
	char *addnew;

	lenght1 = str_len(key);
	lenght2 = str_len(value);
	addnew = malloc(sizeof(char) * (lenght1 + lenght2 + 2));
	if (addnew == NULL)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		addnew[i] = key[i];
	addnew[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		addnew[i + 1 + j] = value[j];
	addnew[i + 1 + j] = '\0';
	return (addnew);
}

/**
 * _atoi - function converts string to an integer
 * @str: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int n, integer;
	int number = 0, num_test;

	num_test = INT_MAX;
	for (integer = 0; num_test != 0; integer++)
		num_test /= 10;
	for (n = 0; str[n] != '\0' && n < integer; n++)
	{
		number *= 10;
		if (str[n] < '0' || str[n] > '9')
			return (-1);
		if ((n == integer - 1) && (str[n] - '0' > INT_MAX % 10))
			return (-1);
		number += str[n] - '0';
		if ((n == integer - 2) && (str[n + 1] != '\0') && (number > INT_MAX / 10))
			return (-1);
	}
	if (n > integer)
		return (-1);
	return (number);
}
