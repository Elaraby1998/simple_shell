#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - a fun that creates a copy of the environment
 * Return: If an error occurs a double pointer to the new copy
 */

char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int idx;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (idx = 0; environ[idx]; idx++)
	{
		new_environ[idx] = malloc(_strlen(environ[idx]) + 1);

		if (!new_environ[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(new_environ[idx]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[idx], environ[idx]);
	}
	new_environ[idx] = NULL;

	return (new_environ);
}

/**
 * free_env - a fun frees the the environment copy
 */

void free_env(void)
{
	int idx;

	for (idx = 0; environ[idx]; idx++)
		free(environ[idx]);
	free(environ);
}

/**
 * _getenv - a fun that gets an environmental variable from the PATH
 * @var: a name of the environmental variable to get
 * Return: the environmental variable does not exist - NULL
 * Otherwise - the pointer to the environmental variable
 */

char **_getenv(const char *var)
{
	int idx, lgth;

	lgth = _strlen(var);
	for (idx = 0; environ[idx]; idx++)
	{
		if (_strncmp(var, environ[idx], lgth) == 0)
			return (&environ[idx]);
	}

	return (NULL);
}

