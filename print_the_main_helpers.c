#include "shell.h"

/**
 * _print - functionn that writes arrays of char in the stdr output.
 *
 * @string: the pointer to the array of char.
 *
 * Return: numb of bytes writed, -1 on error.
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, string_length(string)));
}

/**
 * _printer_ - a function that writes array of char in standarerror.
 *
 * @string: the pointer to the array of char.
 *
 * Return: the numb of bytes writed or -1 otherwise.
 */

int _printer_(char *string)
{
	return (write(STDERR_FILENO, string, string_length(string)));
}

/**
 * _error_print -  function that writes an array of char
 *                in the standart error.
 *
 * @data: the main pointer to the program data.
 * @errorcode: the error code to print.
 *
 * Return: the number of bytes writed or -1 on error.
 */

int _error_print(int errorcode, data_of_programm *data)
{
	char n_as_stg[10] = {'\0'};

	numm_string_transformer((long) data->exec_counter, n_as_stg, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printer_(data->program_name);
		_printer_(": ");
		_printer_(n_as_stg);
		_printer_(": ");
		_printer_(data->tokens[0]);
		if (errorcode == 2)
			_printer_(": Illegal number: ");
		else
			_printer_(": can't cd to ");
		_printer_(data->tokens[1]);
		_printer_("\n");
	}
	else if (errorcode == 127)
	{
		_printer_(data->program_name);
		_printer_(": ");
		_printer_(n_as_stg);
		_printer_(": ");
		_printer_(data->command_name);
		_printer_(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printer_(data->program_name);
		_printer_(": ");
		_printer_(n_as_stg);
		_printer_(": ");
		_printer_(data->command_name);
		_printer_(": Permission denied\n");
	}
	return (0);
}
