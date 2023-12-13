#include "shell.h"

/**
 * tokenising_part - function that separate the string using a delimiter.
 *
 * @data: pointer to the program data.
 *
 * Return: array of the different parts of the string
 */
void tokenising_part(data_of_programm *data)
{
        char *delimit = " \t";
        int i, x, counterrr = 2, length;

        length = string_length(data->input_line);
        if (length)
        {
                if (data->input_line[length - 1] == '\n')
                        data->input_line[length - 1] = '\0';
        }

        for (i = 0; data->input_line[i]; i++)
        {
                for (x = 0; delimit[x]; x++)
                {
                        if (data->input_line[i] == delimit[x])
                                counterrr++;
                }
        }
        data->tokens = malloc(counterrr * sizeof(char *));
        if (data->tokens == NULL)
        {
                perror(data->program_name);
                exit(errno);
        }
        i = 0;
        data->tokens[i] = double_the_string(string_separator(data->input_line, delimit));
        data->command_name = double_the_string(data->tokens[0]);

        while (data->tokens[i++])
        {
                data->tokens[i] = double_the_string(string_separator(NULL, delimit));
        }
}
