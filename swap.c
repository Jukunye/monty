#include "monty.h"

/**
 * swap - swaps the top two elements of the stack
 * @stack: pointer to the stack
 * @line_number: corresponding line
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int i, tos, tos1;
	stack_t *temp = *stack;

	if (temp->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_SUCCESS);
	}

	tos = pop_int(stack);
	tos1 = pop_int(stack);

	i = add_dnodeint(stack, tos);
	i = add_dnodeint(stack, tos1);

	(void)i;
}
