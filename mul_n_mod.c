#include "monty.h"

/**
 * mul - multiplies the second top element of the stack with the top element
 * @stack: pointer to the stack
 * @line_number: number of the line
 */
void mul(stack_t **stack, unsigned int line_number)
{
	int i, tos, tos1;
	stack_t *temp = *stack;

	if (temp == NULL || temp->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_FAILURE);
	}

	tos = pop_int(stack);
	tos1 = pop_int(stack);

	tos1 *= tos;

	i = add_dnodeint(stack, tos1);

	(void)i;
}

/**
 * mod - computes the rest of the division of the second top element of
 *	the stack by the top element of the stack.
 * @stack: pointer to the stack
 * @line_number: corresponding line number
 */
void mod(stack_t **stack, unsigned int line_number)
{
	int i, tos, tos1;
	stack_t *temp = *stack;

	if (temp == NULL || temp->next == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_SUCCESS);
	}

	tos = pop_int(stack);
	tos1 = pop_int(stack);

	if (tos == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_SUCCESS);
	}

	tos1 %= tos;

	i = add_dnodeint(stack, tos1);

	(void)i;
}
