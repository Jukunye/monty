#include "monty.h"

/**
 * pop - removes the top element of the stack
 * @stack: pointer to stack
 * @line_number: number of line
 */
void pop(stack_t **stack, unsigned int line_number)
{
	int poped_int;
	stack_t *temp = *stack;

	if (temp != NULL)
	{
		poped_int = pop_int(stack);
		(void)poped_int;
		return;
	}

	fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
	free_array(tokens);
	exit(EXIT_FAILURE);
}

/**
 * pop_int - remove the to of stack integer and returns it
 * @stack: address of stack
 *
 * Return: integer poped
 */
int pop_int(stack_t **stack)
{
	int poped_int;
	stack_t *temp, *current = *stack;

	temp = current;
	poped_int = current->n;
	current = current->next;
	free(temp);

	*stack = current;

	return (poped_int);
}
