#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
/*********** THE MACROS ************/
#include "macros.h" 
/*********** THE MAINSTRUCTURES ************/

/**
 * struct info-  the main struct for the program data
 * @program_name: name of the executable
 * @input_line: the pointer to the input read for _getlin
 * @command_name: the pointer to the first command typed by the user
 * @exec_counter: the number of excecuted comands
 * @file_descriptor: main file descriptor to the input of commands
 * @tokens: main pointer to array of tokenized input
 * @env:  the copy of the environ
 * @alias_list: an array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_programm;


/**
 * struct builtins - the mainstruct for the builtins.
 * @builtin:  name of the builtin.
 * @function:  associated function to be called for each builtin.
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_programm *data);
} builtins;


/*********** THE  MAIN FUNCTIONS ***********/



void i_data(data_of_programm *data, int arc, char *argv[], char **env);

void prommpt_looper(char *prompt, data_of_programm *data);

void handle_ctrl_c(int opr UNUSED);


int _getlin(data_of_programm *data);

int ops_chekers(char *array_comnd[], int i, char array_op[]);


void varr_exp(data_of_programm *data);

void alias_exxpen(data_of_programm *data);

int the_buffuer_add(char *buffer, char *str_to_add);



void tokenising_part(data_of_programm *data);

char *string_separator(char *line, char *delim);



int the_executer(data_of_programm *data);


int main_builtinss_list(data_of_programm *data);


char **tokenizer(data_of_programm *data);

int prog_finder(data_of_programm *data);


/************ THe HELPERS FOR MEMORY MGMNT ************/


void free_pointerrs_arrays(char **directories);

void free_the_data(data_of_programm *data);

void free_all_data(data_of_programm *data);


/************ BUILTINS ************/

int exit_from_builtinss(data_of_programm *data);

int c_dir_buitins(data_of_programm *data);

int setting_dir_working(data_of_programm *data, char *new_dir);

int helper_builtinn(data_of_programm *data);

int alias_buitinss(data_of_programm *data);


int env_of_buitinss(data_of_programm *data);

int sett_built_env(data_of_programm *data);

int builtin_unset_env(data_of_programm *data);


/************ THE HELPERS FOR ENVIRONMENT VAR MANAGEMENT ************/

char *envirnmnt_key(char *name, data_of_programm *data);

int envrnmnt_stkey(char *key, char *value, data_of_programm *data);

int envrnmt_removekey(char *key, data_of_programm *data);

void envirnmnt_printer(data_of_programm *data);


/************** THE HELPERS FOR PRINTING **************/

int _print(char *string);

int _printer_(char *string);

int _error_print(int errorcode, data_of_programm *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/

int string_length(char *string);

char *double_the_string(char *string);

int string_comparer(char *string1, char *string2, int number);

char *string_concater(char *string1, char *string2);

void reverse_string(char *string);

void numm_string_transformer(long number, char *string, int base);

int str_int_transformer(char *s);

int char_count(char *string, char *character);

int alias_control(data_of_programm *data, char *alias);

char *alias_bringing(data_of_programm *data, char *alias);

int to_set_alias(char *alias_string, data_of_programm *data);

#endif
