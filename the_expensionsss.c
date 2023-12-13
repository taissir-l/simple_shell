#include "shell.h"

/**
 * varr_exp - a function that expands variables.
 *
 * @data: the pointer to structure of the program data.
 *
 * Return: void.
 */
void varr_exp(data_of_programm *data)
{
	int x, y;
	char line[BUFFER_SZE] = {0}, expansion[BUFFER_SZE] = {'\0'}, *tem;

	if (data->input_line == NULL)
		return;
	the_buffuer_add(line, data->input_line);
	for (x = 0; line[x]; x++)
		if (line[x] == '#')
			line[x--] = '\0';
		else if (line[x] == '$' && line[x + 1] == '?')
		{
			line[x] = '\0';
			numm_string_transformer(errno, expansion, 10);
			the_buffuer_add(line, expansion);
			the_buffuer_add(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && line[x + 1] == '$')
		{
			line[x] = '\0';
			numm_string_transformer(getpid(), expansion, 10);
			the_buffuer_add(line, expansion);
			the_buffuer_add(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && (line[x + 1] == ' ' || line[x + 1] == '\0'))
			continue;
		else if (line[x] == '$')
		{
			for (y = 1; line[x + y] && line[x + y] != ' '; y++)
				expansion[y - 1] = line[x + y];
			tem = envirnmnt_key(expansion, data);
			line[x] = '\0', expansion[0] = '\0';
			the_buffuer_add(expansion, line + x + y);
			tem ? the_buffuer_add(line, tem) : 1;
			the_buffuer_add(line, expansion);
		}
	if (!string_comparer(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = double_the_string(line);
	}
}
/**
 * alias_exxpen - a function that expan the  alias.
 *
 * @data: the pointer to struct of the program data.
 *
 * Return: void.
 */

void alias_exxpen(data_of_programm *data)
{
	int i, j, was_expnd = 0;

	char line[BUFFER_SZE] = {0}, expansion[BUFFER_SZE] = {'\0'}, *tem;

	if (data->input_line == NULL)
		return;

	the_buffuer_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		tem = alias_bringing(data, expansion);
		if (tem)
		{
			expansion[0] = '\0';
			the_buffuer_add(expansion, line + i + j);
			line[i] = '\0';
			the_buffuer_add(line, tem);
			line[string_length(line)] = '\0';
			the_buffuer_add(line, expansion);
			was_expnd = 1;
		}
		break;
	}

	if (was_expnd)
	{
		free(data->input_line);
		data->input_line = double_the_string(line);
	}
}


/**
 * the_buffuer_add - a function that append string at end of buffer.
 *
 * @buffer: the main buffer to be filled.
 * @str_to_add: the string copied in the buffer.
 *
 * Return: void.
 */

int the_buffuer_add(char *buffer, char *str_to_add)
{
	int leng, x;

	leng = string_length(buffer);
	for (x = 0; str_to_add[x]; x++)
	{
		buffer[leng + x] = str_to_add[x];
	}

	buffer[leng + x] = '\0';
	return (leng + x);
}

