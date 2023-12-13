#include "shell.h"
/**
 * _getlin - function that read one line from prompt.
 *
 * @data: struct for the program's data
 *
 * Return: the counting bytes.
*/

int _getlin(data_of_programm *data)
{
        char buff[BUFFER_SZE] = {'\0'};
        static char *array_comnd[10] = {NULL};
        static char array_op[10] = {'\0'};
        ssize_t bytes_read, i = 0;

        if (!array_comnd[0] || (array_op[0] == '&' && errno != 0) ||
                (array_op[0] == '|' && errno == 0))
        {
                for (i = 0; array_comnd[i]; i++)
                {
                        free(array_comnd[i]);
                        array_comnd[i] = NULL;
                }

                bytes_read = read(data->file_descriptor, &buff, BUFFER_SZE - 1);
                if (bytes_read == 0)
                        return (-1);

                i = 0;

                do {
                        array_comnd[i] = double_the_string(string_separator(i ? NULL : buff, "\n;"));
                        i = ops_chekers(array_comnd, i, array_op);
                } while (array_comnd[i++]);
        }
        data->input_line = array_comnd[0];
        for (i = 0; array_comnd[i]; i++)
        {
                array_comnd[i] = array_comnd[i + 1];
                array_op[i] = array_op[i + 1];
        }
        return (string_length(data->input_line));
}

/**
 * ops_chekers - function that checks and split for && and ||.
 *
 * @array_comnd: array of the commands.
 * @i: index in the array_comnd to be checked
 * @array_op: array of the logical operators for each previous command
 *
 * Return: index of the last command in the array_comnd.
 */

int ops_chekers(char *array_comnd[], int i, char array_op[])
{
        char *temm = NULL;
        int j;

        /* checks for the & char in the command line*/
        for (j = 0; array_comnd[i] != NULL  && array_comnd[i][j]; j++)
        {
                if (array_comnd[i][j] == '&' && array_comnd[i][j + 1] == '&')
                {
                        temm = array_comnd[i];
                        array_comnd[i][j] = '\0';
                        array_comnd[i] = double_the_string(array_comnd[i]);
                        array_comnd[i + 1] = double_the_string(temm + j + 2);
                        i++;
                        array_op[i] = '&';
                        free(temm);
                        j = 0;
                }
                if (array_comnd[i][j] == '|' && array_comnd[i][j + 1] == '|')
                {
                        temm = array_comnd[i];
                        array_comnd[i][j] = '\0';
                        array_comnd[i] = double_the_string(array_comnd[i]);
                        array_comnd[i + 1] = double_the_string(temm + j + 2);
                        i++;
                        array_op[i] = '|';
                        free(temm);
                        j = 0;
                }
        }
        return (i);
}

