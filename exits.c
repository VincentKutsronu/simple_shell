#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	char *s = dest;

	for (int i = 0; i < n - 1 && src[i] != '\0'; i++) {
		dest[i] = src[i];
	}

	if (n > 0) {
		dest[n - 1] = '\0';
	}

	return (s);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	char *s = dest;

	int i = 0;
	while (dest[i] != '\0') {
		i++;
	}

	int j = 0;
	while (src[j] != '\0' && j < n) {
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n) {
		dest[i] = '\0';
	}

	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0') {
		if (*s == c) {
			return (s);
		}

		s++;
	}

	return (NULL);
}
