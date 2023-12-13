#include "shell.h"

int cheking_files(char *full_path);


/**
 * prog_finder - a function that find a program in path
 *
 * @data: a pointer to the program's data
 *
 * Return: 0 if success error otherwise.
 */


int prog_finder(data_of_programm *data)
{
	int i = 0, re_code = 0;
	char **direct;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (cheking_files(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = string_concater(double_the_string("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	direct = tokenizer(data);

	if (!direct || !direct[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; direct[i]; i++)
	{
		direct[i] = string_concater(direct[i], data->tokens[0]);
		re_code = cheking_files(direct[i]);
		if (re_code == 0 || re_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = double_the_string(direct[i]);
			free_pointerrs_arrays(direct);
			return (re_code);
		}
	}

	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_pointerrs_arrays(direct);
	return (re_code);
}


/**
 * tokenizer - a function that tokenizes the path of direc.
 *
 * @data: the pointer to program data.
 *
 * Return: the path directories.
 */

char **tokenizer(data_of_programm *data)
{
	int i = 0;
	int count_dirc = 2;
	char **tkn = NULL;
	char *PATH;

	PATH = envirnmnt_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = double_the_string(PATH);
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			count_dirc++;
	}

	tkn = malloc(sizeof(char *) * count_dirc);
	i = 0;
	tkn[i] = double_the_string(string_separator(PATH, ":"));

	while (tkn[i++])
	{
		tkn[i] = double_the_string(string_separator(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tkn);
}

/**
 * cheking_files -  afunction that checks if exists file or not a dairectory
 *                 if it has excecution permisions for permisions.
 *
 * @full_path: the main pointer to full file name.
 *
 * Return: 0 on success or error otherwise.
 */

int cheking_files(char *full_path)
{
	struct stat ssb;

	if (stat(full_path, &ssb) != -1)
	{
		if (S_ISDIR(ssb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
