#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - a fun locates a character in a string
 * @s: aa string to be searched
 * @c: a character to be located
 * Return: if c is found - a pointer to the first occurence
 * if c is not found - NULL
 */

char *_strchr(char *s, char c)
{
	int idx;

	for (idx = 0; s[idx]; idx++)
	{
		if (s[idx] == c)
			return (s + idx);
	}

	return (NULL);
}

/**
 * _strspn - a function that gets the length of a prefix substring
 * @s: the string to be searched
 * @accept: the prefix to be measured
 * Return: the number of bytes in s which
 * consist only of bytes from accept
 */

int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int idx;

	while (*s)
	{
		for (idx = 0; accept[idx]; idx++)
		{
			if (*s == accept[idx])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - a fun compares two strings
 * @s1: a first string to be compared
 * @s2: a second string to be compared
 * Return: a positive byte difference if s1 > s2
 * 0 if s1 = s2
 * Negative byte difference if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - a fun that compare two strings
 * @s1: a pointer to a string
 * @s2: a pointer to a string
 * @n: a first n bytes of the strings to compare
 * Return: less than 0 if s1 is shorter than s2
 * 0 if s1 and s2 match
 * Greater than 0 if s1 is longer than s2
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t v;

	for (v = 0; s1[v] && s2[v] && v < n; v++)
	{
		if (s1[v] > s2[v])
			return (s1[v] - s2[v]);
		else if (s1[v] < s2[v])
			return (s1[v] - s2[v]);
	}
	if (v == n)
		return (0);
	else
		return (-15);
}

