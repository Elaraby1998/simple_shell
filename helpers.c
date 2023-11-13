#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - a fun frees up memory taken by args
 * @args: the null-terminated double pointer containing commands/arguments
 * @front: the double pointer to the beginning of args
 */
void free_args(char **args, char **front)
{
	size_t v;

	for (v = 0; args[v] || args[v + 1]; v++)
		free(args[v]);

	free(front);
}

/**
 * get_pid - a fun gets the current process ID
 * Description: it opens a stat file, a space-delimited file containing
 * information about the current process The PID is the
 * first word in the file, The function reads the PID into
 * a buffer and replace the space at the end with a \0 byte
 * Return: a current process ID or NULL on failure
 */
char *get_pid(void)
{
	size_t x = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[x] != ' ')
		x++;
	buffer[x] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - a fun gets the value corresponding to
 * an environmental variable
 * @beginning: a environmental variable to search for
 * @len: a length of the environmental variable to search for
 * Return: If the variable is not found - an empty string
 * Otherwise : the value of the environmental variable
 * Description: variables are stored in the format VARIABLE=VALUE
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - a fun handles variable replacement
 * @line: the double pointer containing the command and arguments
 * @exe_ret: the pointer to the return value of the last executed command
 * Description: It replaces $$ with the current PID, $? with the return value
 * of the last executed program, and envrionmental variables
 * preceded by $ with their corresponding value
 */

void variable_replacement(char **line, int *exe_ret)
{
	int o, i = 0, length;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (o = 0; old_line[o]; o++)
	{
		if (old_line[o] == '$' && old_line[o + 1] &&
				old_line[o + 1] != ' ')
		{
			if (old_line[o + 1] == '$')
			{
				replacement = get_pid();
				i = o + 2;
			}
			else if (old_line[o + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				i = o + 2;
			}
			else if (old_line[o + 1])
			{
				/* extract the variable name to search for */
				for (i = o + 1; old_line[i] &&
						old_line[i] != '$' &&
						old_line[i] != ' '; i++)
					;
				length = i - (o + 1);
				replacement = get_env_value(&old_line[o + 1], length);
			}
			new_line = malloc(o + _strlen(replacement)
					  + _strlen(&old_line[i]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, o);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[i]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			o = -1;
		}
	}
}

