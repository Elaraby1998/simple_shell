#include "shell.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);

/**
 * get_args - a fun gets a command from standard input
 * @line: the buffer to store the command
 * @exe_ret: the return value of the last executed command
 * Return: if an error occurs - NULL
 * Otherwise : a pointer to the stored command
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - a fun that partitions operators from commands and calls
 * them
 * @args: the array of arguments
 * @front: the double pointer to the beginning of args
 * @exe_ret: a return value of the parent process' last executed command
 * Return: a return value of the last executed command
 */

int call_args(char **args, char **front, int *exe_ret)
{
	int ret, idx;

	if (!args[0])
		return (*exe_ret);
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], "||", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
		else if (_strncmp(args[idx], "&&", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - a fun that calls the execution of a command
 * @args: the array of arguments
 * @front: the double pointer to the beginning of args
 * @exe_ret: a return value of the parent process' last executed command
 * Return: a return value of the last executed command
 */

int run_args(char **args, char **front, int *exe_ret)
{
	int ret, v;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (v = 0; args[v]; v++)
		free(args[v]);
	return (ret);
}

/**
 * handle_args - a fun gets, calls, and runs the execution of a command
 * @exe_ret: a return value of the parent process' last executed command
 * Return: if an end-of-file is read - END_OF_FILE (-2)
 * If the input cannot be tokenized - -1
 * O/w - the exit value of the last executed command
 */

int handle_args(int *exe_ret)
{
	int ret = 0, idx;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], ";", 1) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++idx];
			idx = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - a fun checks if there are any leading ';', ';;', '&&', or '||'
 * @args: a 2D pointer to tokenized commands and arguments
 * Return: if a ';', '&&', or '||' is placed at an invalid position - 2
 * Otherwise : 0
 */
int check_args(char **args)
{
	size_t v;
	char *cur, *nex;

	for (v = 0; args[v]; v++)
	{
		cur = args[v];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (v == 0 || cur[1] == ';')
				return (create_error(&args[v], 2));
			nex = args[v + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[v + 1], 2));
		}
	}
	return (0);
}

