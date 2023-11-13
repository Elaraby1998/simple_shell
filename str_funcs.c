#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - a fun returns the length of a string
 * @s: the pointer to the characters string
 * Return: the length of the character string
 */
int _strlen(const char *s)
{
	int lgth = 0;

	if (!s)
		return (lgth);
	for (lgth = 0; s[lgth]; lgth++)
		;
	return (lgth);
}

/**
 * _strcpy - a fun copies the string pointed to by src, including the
 * terminating null byte, to the buffer pointed by des
 * @dest: a pointer to the destination of copied string
 * @src: a pointer to the src of the source string
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t v;

	for (v = 0; src[v] != '\0'; v++)
		dest[v] = src[v];
	dest[v] = '\0';
	return (dest);
}

/**
 * _strcat - a fun concantenates two strings
 * @dest: the pointer to destination string
 * @src: the pointer to source string
 * Return: a pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - a fun concantenates two strings where n number
 * of bytes are copied from source
 * @dest: a pointer to destination string
 * @src: the pointer to source string
 * @n: a n bytes to copy from src
 * Return: pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t v;

	for (v = 0; v < n && src[v] != '\0'; v++)
		dest[dest_len + v] = src[v];
	dest[dest_len + v] = '\0';

	return (dest);
}

