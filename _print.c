#include "monty.h"

/**
 * pall - prints all the values on the stack, starting from the top of stack.
 * @stack: pointer to the stack
 * @line_number: corresponding line number
 *
 * Return: nothing
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * pint - prints the value at the top of the stack
 * @stack: pointer to the stack
 * @line_number: corresponding line number
 *
 * Return: nothing
 */
void pint(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (temp != NULL)
	{
		printf("%d\n", temp->n);
		return;
	}

	fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
	free_array(tokens);
	exit(EXIT_FAILURE);
}

/**
 * nop - doesn't do anything
 * @stack: pointer to stack
 * @line_number: correspoinding line
 *
 * Return: nothing
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
