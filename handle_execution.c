#include "monty.h"

/**
  * handle_execution - Manages the operations to be executed by the interpreter
  * @op_code: The operation code to manage
  * @op_param: The parameter of the instruction
  * @line: The line on which the error occurred
  * @m: The method to be used by the interpreter
  *
  * Return: 0 if the operation was executed correctly or errcode if is invalid
  */
int handle_execution(char *op_code, char *op_param, unsigned int line, int m)
{
	int status_op = 0;
	void (*oprt)(stack_t **, unsigned int);

	if (strcmp(op_code, "stack") == 0)
		return (METH_STACK);
	else if (strcmp(op_code, "queue") == 0)
		return (METH_QUEUE);

	oprt = pick_func(op_code);
	if (oprt)
	{
		if (strcmp(op_code, "push") == 0)
		{
			status_op = check_push_param(op_param);
			if (status_op == ERR_PUSH_USG)
				return (ERR_PUSH_USG);

			if (m != 0 && m == METH_QUEUE)
				oprt = pick_func("push_queue");

			oprt(&head, atoi(op_param));
		}
		else
		{
			oprt(&head, line);
		}

		return (m);
	}

	return (ERR_BAD_INST);
}
