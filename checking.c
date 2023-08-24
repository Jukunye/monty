#include "monty.h"

/**
  * check_args_num - Check the arguments passed on to the interpreter
  * @argn: Number of args
  *
  * Return: Nothing
  */
void check_args_num(int argn)
{
	if (argn != MIN_ARGS)
		handle_error(ERR_ARG_USG, NULL, 0, NULL);
}

/**
  * check_access_rights - CChecks if the user has permissions to read the file
  * @filename: The pathname of the file
  *
  * Return: Nothing
  */
void check_access_rights(char *filename)
{
	if (access(filename, R_OK) == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
}

/**
  * check_push_param - Check the parameter of the push instruction
  * @param: The parameter to be verified
  *
  * Return: 0 if is a valid param or errcode if is invalid
  */
int check_push_param(char *param)
{
	if (param == NULL || check_digits(param) == 0)
		return (ERR_PUSH_USG);

	return (VALID_PARM);
}

/**
  * check_digits - Checks if all characters in a string are digits
  * @s: The string to be evaluated
  *
  * Return: 1 if all if all evaluated characters are digits or 0 if not
  */
int check_digits(char *s)
{
	int status = 1;

	while (*s != '\0')
	{
		if (s[0] == 45)
		{
			++s;
			continue;
		}

		if (isdigit(*s) == 0)
		{
			status = 0;
			return (status);
		}

		++s;
	}

	return (status);
}
