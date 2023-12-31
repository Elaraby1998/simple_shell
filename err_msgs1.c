#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - a fun= creates an error message for permission denied failures
 * @args: the array of arguments passed to the command
 * Return: an error string
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int lgth;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	lgth = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (lgth + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - a fun creates an error message for command not found failures
 * @args: the array of arguments passed to the command
 * Return: an error string
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int lgth;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	lgth = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (lgth + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}

