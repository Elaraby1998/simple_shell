#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - a fun locates the delimiter idx marking the end
 * of the first token contained within a string
 * @str: teh string to be searched
 * @delim: teh delimiter character
 * Return: delimiter idx marking the end of
 * the intitial token pointed to be str
 */

int token_len(char *str, char *delim)
{
	int idx = 0, lgth = 0;

	while (*(str + idx) && *(str + idx) != *delim)
	{
		lgth++;
		idx++;
	}
	return (lgth);
}

/**
 * count_tokens - a fun counts the number of delimited
 * words contained within a string
 * @str: a string to be searched
 * @delim: a delimiter character
 * Return: a number of words contained within str
 */

int count_tokens(char *str, char *delim)
{
	int idx, tokens = 0, lgth = 0;

	for (idx = 0; *(str + idx); idx++)
		lgth++;

	for (idx = 0; idx < lgth; idx++)
	{
		if (*(str + idx) != *delim)
		{
			tokens++;
			idx += token_len(str + idx, delim);
		}
	}
	return (tokens);
}

/**
 * _strtok - a fun tokenizes a string
 * @line: a string
 * @delim: a delimiter character to tokenize the string by
 * Return: the pointer to an array containing the tokenized words
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int idx = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[idx] == *delim)
			idx++;

		letters = token_len(line + idx, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[idx];
			idx++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

