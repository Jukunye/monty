#include "monty.h"

/**
 * add - adds the top two elements of the stack
 * @stack: stack pointer
 * @line_number: number of line
 */
void add(stack_t **stack, unsigned int line_number)
{
	int i, tos, tos1;
	stack_t *temp = *stack;

	if (temp == NULL || temp->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_FAILURE);
	}

	tos = pop_int(stack);
	tos1 = pop_int(stack);

	tos += tos1;

	i = add_dnodeint(stack, tos);

	(void)i;
}

/**
 * sub - subtrackts the top element of the stack from the second top element
 * @stack: pointer to the stack
 * @line_number: corresponding line number
 */
void sub(stack_t **stack, unsigned int line_number)
{
	int i, tos, tos1;
	stack_t *temp = *stack;

	if (temp == NULL || temp->next == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_SUCCESS);
	}

	tos = pop_int(stack);
	tos1 = pop_int(stack);

	tos1 -= tos;

	i = add_dnodeint(stack, tos1);

	(void)i;
}
