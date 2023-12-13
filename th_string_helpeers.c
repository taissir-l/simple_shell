#include "shell.h"
/**
 * string_length - function that returns the length of string.
 *
 * @string: thr pointer to the string.
 *
 * Return: the leng of string.
 */

int string_length(char *string)
{
	int leng = 0;

	if (string == NULL)
		return (0);

	while (string[leng++] != '\0')
	{
	}
	return (--leng);
}
/**
 * double_the_string - function to duplicate a string.
 *
 * @string: String.
 *
 * Return: the pointer to array.
 */

char *double_the_string(char *string)
{
	char *r;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = string_length(string) + 1;

	r = malloc(sizeof(char) * len);

	if (r == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		r[i] = string[i];
	}

	return (r);
}
/**
 * string_comparer - a function that Compares two strings.
 *
 * @string1: String the shorter.
 * @string2: String the longer.
 * @number: number of characters to be compared..
 *
 * Return: 1 if  strings  equals,0 if  strings  are not equal.
 */

int string_comparer(char *string1, char *string2, int number)
{
	int i;

	if (string1 == NULL && string2 == NULL)
		return (1);
	if (string1 == NULL || string2 == NULL)
		return (0);
	if (number == 0) /* infinite longitud */
	{
		if (string_length(string1) != string_length(string2))
			return (0);
		for (i = 0; string1[i]; i++)
		{
			if (string1[i] != string2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < number ; i++)
		{
			if (string1[i] != string2[i])
			return (0);
		}		
		return (1);
	}
}
/**
 * string_concater - function that concatenates two strings.
 *
 * @string1: String .
 * @string2: String 2.
 *
 * Return: the pointer to the array.
 */

char *string_concater(char *string1, char *string2)
{
	char *r;
	int leng1 = 0, leng2 = 0;

	if (string1 == NULL)
		string1 = "";
	leng1 = string_length(string1);

	if (string2 == NULL)
		string2 = "";
	leng2 = string_length(string2);

	r = malloc(sizeof(char) * (leng1 + leng2 + 1));
	if (r == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (leng1 = 0; string1[leng1] != '\0'; leng1++)
		r[leng1] = string1[leng1];
	free(string1);
	for (leng2 = 0; string2[leng2] != '\0'; leng2++)
	{
		r[leng1] = string2[leng2];
		leng1++;
	}

	r[leng1] = '\0';
	return (r);
}
/**
 * reverse_string - a function that reverses a string.
 *
 * @string: the pointer to string.
 *
 * Return: void.
 */
void reverse_string(char *string)
{

	int i = 0, leng = string_length(string) - 1;
	char hold;

	while (i < leng)
	{
		hold = string[i];
		string[i++] = string[leng];
		string[leng--] = hold;
	}
}
