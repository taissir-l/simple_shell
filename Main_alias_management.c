#include "shell.h"

/**
 * alias_control - function to add and remove or show aliase.
 *
 * @data: data.
 * @alias: alias to be printed.
 *
 * Return: 0 when sucess or other number if its declared in the arguments.
 */

int alias_control(data_of_programm *data, char *alias)
{
        int i, j, alias_leng;
        char buffer[250] = {'\0'};

        if (data->alias_list)
        {
                alias_leng = string_length(alias);
                for (i = 0; data->alias_list[i]; i++)
                {
                        if (!alias || (string_comparer(data->alias_list[i], alias, alias_leng)
                                &&      data->alias_list[i][alias_leng] == '='))
                        {
                                for (j = 0; data->alias_list[i][j]; j++)
                                {
                                        buffer[j] = data->alias_list[i][j];
                                        if (data->alias_list[i][j] == '=')
                                                break;
                                }

                                buffer[j + 1] = '\0';
                                the_buffuer_add(buffer, "'");
                                the_buffuer_add(buffer, data->alias_list[i] + j + 1);
                                the_buffuer_add(buffer, "'\n");
                                _print(buffer);
                        }
                }
        }
        return (0);
}

/**
 * alias_bringing - function to add and remove or show aliases.
 *
 * @data: the main struct for the program data.
 * @name: name of alias.
 *
 * Return: 0 if sucess, or other number if its declared in the arguments.
 */
char *alias_bringing(data_of_programm *data, char *name)
{
        int i, alias_leng;

        if (name == NULL || data->alias_list == NULL)
                return (NULL);
        alias_leng = string_length(name);

        for (i = 0; data->alias_list[i]; i++)
        {
                if (string_comparer(name, data->alias_list[i], alias_leng) &&
                        data->alias_list[i][alias_leng] == '=')
                {
                        return (data->alias_list[i] + alias_leng + 1);
                }
        }

        return (NULL);
}

/**
 * to_set_alias - function to add and or override alias.
 *
 * @alias_string: alias.
 * @data:  program data.
 *
 * Return: 0 if sucess, or other number if its declared in the arguments.
 */

int to_set_alias(char *alias_string, data_of_programm *data)
{
        int i, j;
        char buffer[250] = {'0'}, *temm = NULL;

        if (alias_string == NULL ||  data->alias_list == NULL)
                return (1);

        for (i = 0; alias_string[i]; i++)
                if (alias_string[i] != '=')
                        buffer[i] = alias_string[i];
                else
                {
                        temm = alias_bringing(data, alias_string + i + 1);
                        break;
                }

        for (j = 0; data->alias_list[j]; j++)
                if (string_comparer(buffer, data->alias_list[j], i) &&
                        data->alias_list[j][i] == '=')
                {
                        free(data->alias_list[j]);
                        break;
                }

        if (temm)
        {
                the_buffuer_add(buffer, "=");
                the_buffuer_add(buffer, temm);
                data->alias_list[j] = double_the_string(buffer);
        }

        else
                data->alias_list[j] = double_the_string(alias_string);
        return (0);
}
