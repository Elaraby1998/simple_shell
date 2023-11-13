#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - a fun that counts the digit length of a number
 * @num: a number to measure
 * Return: a digit length
 */

int num_len(int num)
{
	unsigned int number;
	int lgth = 1;

	if (num < 0)
	{
		lgth++;
		number = num * -1;
	}
	else
	{
		number = num;
	}
	while (number > 9)
	{
		lgth++;
		number /= 10;
	}

	return (lgth);
}

/**
 * _itoa - a function that converts an integer to a string
 * @num: the integer
 * Return: the converted string
 */

char *_itoa(int num)
{
	char *buffer;
	int lgth = num_len(num);
	unsigned int number;

	buffer = malloc(sizeof(char) * (lgth + 1));
	if (!buffer)
		return (NULL);

	buffer[lgth] = '\0';

	if (num < 0)
	{
		number = num * -1;
		buffer[0] = '-';
	}
	else
	{
		number = num;
	}

	lgth--;
	do {
		buffer[lgth] = (number % 10) + '0';
		number /= 10;
		lgth--;
	} while (number > 0);

	return (buffer);
}

/**
 * create_error - a fun writes a custom error message to stderr
 * @args: the array of arguments
 * @err: an error value
 * Return: an error value
 */

int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}

