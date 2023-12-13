#include "shell.h"

/**
 * exit_from_builtinss - function to exit the program with the status.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number iotherwise.
 */

int exit_from_builtinss(data_of_programm *data)
{
        int i;

        if (data->tokens[1] != NULL)
        {
                for (i = 0; data->tokens[1][i]; i++)
                        if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
                                && data->tokens[1][i] != '+')
                        {
                                errno = 2;
                                return (2);
                        }

                errno = str_int_transformer(data->tokens[1]);
        }

        free_all_data(data);
        exit(errno);
}

/**
 * c_dir_buitins - function that will change the current directory.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int c_dir_buitins(data_of_programm *data)
{
        char *dirk_home = envirnmnt_key("HOME", data), *dir_old = NULL;
        char old_dir[128] = {0};
        int eror_code = 0;

        if (data->tokens[1])
        {
                if (string_comparer(data->tokens[1], "-", 0))
                {
                        dir_old = envirnmnt_key("OLDPWD", data);
                        if (dir_old)
                                eror_code = setting_dir_working(data, dir_old);

                        _print(envirnmnt_key("PWD", data));
                        _print("\n");

                        return (eror_code);
                }
                else
                {
                        return (setting_dir_working(data, data->tokens[1]));
                }
        }
        else
        {
                if (!dirk_home)
                        dirk_home = getcwd(old_dir, 128);

                return (setting_dir_working(data, dirk_home));
        }
        return (0);
}

/**
 * setting_dir_working - function that sets the work directory.
 *
 * @data: program data.
 * @new_dir: work directory.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int setting_dir_working(data_of_programm *data, char *new_dir)
{
        char older_dir[128] = {0};
        int e_code = 0;

        getcwd(older_dir, 128);

        if (!string_comparer(older_dir, new_dir, 0))
        {
                e_code = chdir(new_dir);

                if (e_code == -1)
                {
                        errno = 2;
                        return (3);
                }
                envrnmnt_stkey("PWD", new_dir, data);
        }

        envrnmnt_stkey("OLDPWD", older_dir, data);
        return (0);
}

/**
 * helper_builtinn - function to show environment where shell is running.
 *
 * @data: program data.
 *
 * Return: 0 if sucess, or other number otherwise.
 */

int helper_builtinn(data_of_programm *data)
{
        int i, len = 0;
        char *Menajes[6] = {NULL};

        Menajes[0] = HELP_MG;

        if (data->tokens[1] == NULL)
        {
                _print(Menajes[0] + 6);
                return (1);
        }

        if (data->tokens[2] != NULL)
        {
                errno = E2BIG;
                perror(data->command_name);
                return (5);
        }
        Menajes[1] = HELP_EXIT_MG;
        Menajes[2] = HELP_ENV_MG;
        Menajes[3] = HELP_SETENV_MG;
        Menajes[4] = HELP_UNSETENV_MG;
        Menajes[5] = HELP_CD_MG;

        for (i = 0; Menajes[i]; i++)
        {
                len = string_length(data->tokens[1]);
                if (string_comparer(data->tokens[1], Menajes[i], len))
                {
                        _print(Menajes[i] + len + 1);
                        return (1);
                }
        }
        errno = EINVAL;
        perror(data->command_name);

        return (0);
}

/**
 * alias_buitinss - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int alias_buitinss(data_of_programm *data)
{
        int i = 0;

        if (data->tokens[1] == NULL)
                return (alias_control(data, NULL));


        while (data->tokens[++i])
        {
                if (char_count(data->tokens[i], "="))
                        to_set_alias(data->tokens[i], data);
                else
                        alias_control(data, data->tokens[i]);
        }

        return (0);
}

