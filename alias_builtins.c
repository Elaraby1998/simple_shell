#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - a fun that builtin command that either prints all
 * specific aliases
 * @args:  an array of arguments
 * @front: the double pointer to the beginning of args
 * Return: if an error occurs - -1
 * otherwise : 0
 */

int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int v, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (v = 0; args[v]; v++)
	{
		temp = aliases;
		value = _strchr(args[v], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[v], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + v, 1);
		}
		else
			set_alias(args[v], value);
	}
	return (ret);
}

/**
 * set_alias - a fun that will either set an existing alias 'name' with
 * a new value
 * @var_name: the name of the alias
 * @value: the value of the alias. First character
 */

void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, v, i;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (v = 0, i = 0; value[v]; v++)
	{
		if (value[v] != '\'' && value[v] != '"')
			new_value[i++] = value[v];
	}
	new_value[i] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - a fun that prints the alias in the format name='value'
 * @alias: a pointer to an alias
 */

void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_aliases - a fun that goes through the arguments and
 * replace any matching alias with their value
 * @args: a 2D pointer to the arguments
 * Return: a 2D pointer to the arguments
 */

char **replace_aliases(char **args)
{
	alias_t *temp;
	int v;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (v = 0; args[v]; v++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[v], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[v]);
				args[v] = new_value;
				v--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}

