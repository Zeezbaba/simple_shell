#include "shell.h"

/**
 * builtins_check - functions that checks builtin command
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*builtins_check(vars_t *vars))(vars_t *vars)
{
	unsigned int k;
	builtins_t arrays[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (k = 0; arrays[k].f != NULL; k++)
	{
		if (str_cmpr(vars->av[0], arrays[k].name) == 0)
			break;
	}
	if (arrays[k].f != NULL)
		arrays[k].f(vars);
	return (arrays[k].f);
}

/**
 * new_exit - function to exit a program
 * @vars: variables
 * Return: nothing
 */
void new_exit(vars_t *vars)
{
	int status;

	if (str_cmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			std_error(vars, ": Illegal number: ");
			printstdo(vars->av[1]);
			printstdo("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	rel_env_mode(vars->env);
	exit(vars->status);
}

/**
 * _env - functions to print environment
 * @vars: variables
 * Return: nothing.
 */
void _env(vars_t *vars)
{
	unsigned int zeez;

	for (zeez = 0; vars->env[zeez]; zeez++)
	{
		my_putstr(vars->env[zeez]);
		my_putstr("\n");
	}
	vars->status = 0;
}

/**
 * new_setenv - function to create or edit variables
 * @vars: pointer to variables
 *
 * Return: nothing
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		std_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = env_func(vars->env, vars->av[1]);
	if (key == NULL)
		add_keys(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			std_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			rel_env_mode(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - function that remove environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: nothing
 */
void new_unsetenv(vars_t *vars)
{
	char **keys, **environs;

	unsigned int f, k;

	if (vars->av[1] == NULL)
	{
		std_error(vars, ": Incorrect inputs\n");
		vars->status = 2;
		return;
	}
	keys = env_func(vars->env, vars->av[1]);
	if (keys == NULL)
	{
		std_error(vars, ": empty variable");
		return;
	}
	for (f = 0; vars->env[f] != NULL; f++)
		;
	environs = malloc(sizeof(char *) * f);
	if (environs == NULL)
	{
		std_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (f = 0; vars->env[f] != *keys; f++)
		environs[f] = vars->env[f];
	for (k = f + 1; vars->env[k] != NULL; k++, f++)
		environs[f] = vars->env[k];
	environs[f] = NULL;
	free(*keys);
	free(vars->env);
	vars->env = environs;
	vars->status = 0;
}
