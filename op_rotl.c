#include "monty.h"

/**
  * rotl - Rotates the stack to the top
  * @stack: The head of the stack
  * @line_number: The line on which the error occurred
  *
  * Return: Nothing
  */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *curr = *stack;
	unsigned int temp = 0;
	(void) line_number;

	if (curr && curr->next)
	{
		while (curr->next != NULL)
		{
			temp = curr->n;
			curr->n = curr->next->n;
			curr->next->n = temp;
			curr = curr->next;
		}
	}
}
