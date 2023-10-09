#include "shell.h"

/**
 * make_env - create a shell environment from the environment passed to main
 *
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 *
 */

char **make_env(char **env)
{
	char **nc_env = NULL;
	size_t z;

	for (z = 0; env[z] != NULL; z++)
		;

	nc_env = malloc(sizeof(char *) * (z + 1));

	if (nc_env == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}

	for (z = 0; env[z] != NULL; z++)
		nc_env[i] = _strdup(env[z]);
	nc_env[z] = NULL;

	return (nc_env);

}

/**
 * free_env - free environment
 *
 * @env: shell's environment
 *
 * Return: void
 */

void free_env(char **env)
{
	unsigned int a;

	for (a = 0; env[a] != NULL; a++)

	free(env[a]);
	free(env);
}
