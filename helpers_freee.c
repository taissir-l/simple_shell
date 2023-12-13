#include "shell.h"

/**
 * free_the_data - function to free the fields needed each loop
 *
 * @data: the structure of program data.
 *
 * Return: void.
 */
void free_the_data(data_of_programm *data)
{
	if (data->tokens)
		free_pointerrs_arrays(data->tokens);

	if (data->input_line)
		free(data->input_line);

	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - function that will free all field of the data.
 *
 * @data: structure of program data.
 *
 * Return: void.
 */

void free_all_data(data_of_programm *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_the_data(data);

	free_pointerrs_arrays(data->env);

	free_pointerrs_arrays(data->alias_list);
}


/**
 * free_pointerrs_arrays - functionthat frees pointer of array
 *                       corresponding to pointers and arrays.
 *
 * @array: the array of pointers.
 *
 * Return: void.
 */

void free_pointerrs_arrays(char **array)
{
	int x;

	if (array != NULL)
	{
		for (x = 0; array[x]; x++)
			free(array[x]);

		free(array);
		array = NULL;
	}
}
