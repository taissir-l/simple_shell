#include "shell.h"

/**
 * env_of_buitinss -  function that shows the environment
 *                 where the shell runs in program.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int env_of_buitinss(data_of_programm *data)
{
        int i;
        char cpnam[50] = {'\0'};
        char *var_cop = NULL;

        if (data->tokens[1] == NULL)
                envirnmnt_printer(data);
        else
        {
                for (i = 0; data->tokens[1][i]; i++)
                {
                        if (data->tokens[1][i] == '=')
                        {
                                var_cop = double_the_string(envirnmnt_key(cpnam, data));
                                if (var_cop != NULL)
                                        envrnmnt_stkey(cpnam, data->tokens[1] + i + 1, data);
                                envirnmnt_printer(data);

                                if (envirnmnt_key(cpnam, data) == NULL)
                                {
                                        _print(data->tokens[1]);
                                        _print("\n");
                                }
                                else
                                {
                                        envrnmnt_stkey(cpnam, var_cop, data);
                                        free(var_cop);
                                }
                                return (0);
                        }
                        cpnam[i] = data->tokens[1][i];
                }
                errno = 2;
                perror(data->command_name);
                errno = 127;
        }
        return (0);
}


/**
 * sett_built_env - function.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */
int sett_built_env(data_of_programm *data)
{
        if (data->tokens[1] == NULL || data->tokens[2] == NULL)
                return (0);

        if (data->tokens[3] != NULL)
        {
                errno = E2BIG;
                perror(data->command_name);
                return (5);
        }

        envrnmnt_stkey(data->tokens[1], data->tokens[2], data);
        return (0);
}

/**
 * builtin_unset_env - function .
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int builtin_unset_env(data_of_programm *data)
{
        if (data->tokens[1] == NULL)
                return (0);

        if (data->tokens[2] != NULL)
        {
                errno = E2BIG;
                perror(data->command_name);
                return (5);
        }
        envrnmt_removekey(data->tokens[1], data);

        return (0);
}
