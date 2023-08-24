#include "monty.h"

/**
 * operations - executes the appropriate operation based on the opcode
 * @stack: pointer to the stack
 * @line_number: the correspoinding line number
 *
 * Return: nothing
 */
void operations(stack_t **stack, unsigned int line_number)
{
	int i;
	char *op = tokens[0];
	instruction_t operation[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"sub", sub},
		{"mul", mul},
		{"mod", mod},
		{"div", divide},
		{"pstr", pstr},
		{"pchar", pchar},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	for (i = 0; operation[i].opcode != NULL; i++)
	{
		if (strcmp(operation[i].opcode, op) == 0)
		{
			operation[i].f(stack, line_number);
			return;
		}
	}
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, op);
	free_array(tokens);
	free_list(*stack);
	exit(EXIT_FAILURE);
}
