#include "shell.h"

/**
 * numm_string_transformer - function that converts numbers to string.
 *
 * @number: the num to be converted to string.
 * @string: the main buffer to save the number.
 * @base: the base to convert numbr.
 *
 * Return: void.
 */

void numm_string_transformer(long number, char *string, int base)
{
        int i = 0, isNeg = 0;
        long ct = number;
        char l[] = {"0123456789abcdef"};

        if (ct == 0)
                string[i++] = '0';

        if (string[0] == '-')
                isNeg = 1;
        while (ct)
        {
                if (ct < 0)
                        string[i++] = l[-(ct % base)];
                else
                        string[i++] = l[ct % base];
                ct /= base;
        }

        if (isNeg)
                string[i++] = '-';
        string[i] = '\0';

        reverse_string(string);
}


/**
 * str_int_transformer - function that converts string to integer.
 *
 * @s: the pointer to string.
 *
 * Return: int or 0.
 */

int str_int_transformer(char *s)
{
        int sng = 1;
        unsigned int n = 0;

        while (!('0' <= *s && *s <= '9') && *s != '\0')
        {
                if (*s == '-')
                        sng *= -1;
                if (*s == '+')
                        sng *= +1;
                s++;
        }
        while ('0' <= *s && *s <= '9' && *s != '\0')
        {

                n = (n * 10) + (*s - '0');
                s++;
        }

        return (n * sng);
}

/**
 * char_count - function that count the coincidences of
 *                the character in a string.
 *
 * @string: the pointer to string.
 * @character: string with  char to count.
 *
 * Return: int or 0.
 */

int char_count(char *string, char *character)
{
        int i = 0, counte = 0;

        for (; string[i]; i++)
        {
                if (string[i] == character[0])
                        counte++;
        }
        return (counte);
}
