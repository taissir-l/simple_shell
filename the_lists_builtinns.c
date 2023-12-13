#include "shell.h"

/**
 * main_builtinss_list - a function to search for match and execute the builtins.
 *
 * @data: program data.
 *
 * Return: the executed func , -1 otherwise.
 */
int main_builtinss_list(data_of_programm *data)
{
        int iterator;
        builtins options[] = {
                {"exit", exit_from_builtinss},
                {"help", helper_builtinn},
                {"cd", c_dir_buitins},
                {"alias", alias_buitinss},
                {"env", env_of_buitinss},
                {"setenv", sett_built_env},
                {"unsetenv", builtin_unset_env},
                {NULL, NULL}
        };

        for (iterator = 0; options[iterator].builtin != NULL; iterator++)
        {
                if (string_comparer(options[iterator].builtin, data->command_name, 0))
                {
                        return (options[iterator].function(data));
                }
        }

        return (-1);
}
