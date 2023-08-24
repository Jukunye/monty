#include "monty.h"

stack_t *head = NULL;

/**
  * main - The Monty Interpreter entry point
  * @argn: The args number
  * @args: The args passed to the interpreter
  *
  * Return: Always zero
  */
int main(int argn, char *args[])
{
	FILE *fd = NULL;
	size_t line_len = 0;
	unsigned int line_num = 1;
	int readed = 0, op_status = 0;
	char *filename = NULL, *op_code = NULL, *op_param= NULL, *buff = NULL;

	filename = args[1];
	check_args_num(argn);
	fd = open_file(filename);

	while ((readed = getline(&buff, &line_len, fd)) != -1)
	{
		op_code = strtok(buff, "\t\n ");
		if (op_code)
		{
			if (op_code[0] == '#')
			{
				++line_num;
				continue;
			}

			op_param= strtok(NULL, "\t\n ");
			op_status = handle_execution(op_code, op_param, line_num, op_status);

			if (op_status >= 100 && op_status < 300)
			{
				fclose(fd);
				handle_error(op_status, op_code, line_num, buff);
			}
		}

		++line_num;
	}

	frees_stack();
	free(buff);
	fclose(fd);
	return (0);
}
