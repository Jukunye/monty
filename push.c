#include "monty.h"

/**
 * push - pushes an element to the stack
 * @stack: pointer to the stack
 * @line_number: the line
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *endptr;
	int n = (int)strtol(tokens[1], &endptr, 10);

	if (*endptr != '\0')
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		free_array(tokens);
		free_list(*stack);
		exit(EXIT_FAILURE);
	}
	if (!queue_flag)
	{
		if (add_dnodeint(stack, n))
		{
			fprintf(stderr, "Memory allocation: Failed\n");
			free_array(tokens);
			free_list(*stack);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (add_dnodeint_end(stack, n))
		{
			fprintf(stderr, "Memory allocation: Failed\n");
			free_array(tokens);
			free_list(*stack);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * add_dnodeint - adds a node at the beginning of doubly linked list
 * @stack: the stack
 * @n: integer to add
 *
 * Return: (0) on success, otherwise (-1)
 */
int add_dnodeint(stack_t **stack, const int n)
{
	stack_t *new, *temp;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
		return (1);

	new->n = n;
	new->prev = NULL;
	new->next = NULL;

	if (*stack == NULL)
	{
		*stack = new;
		return (0);
	}

	temp = *stack;
	new->next = temp;
	temp->prev = new;
	*stack = new;
	return (0);
}

/**
 * add_dnodeint_end - adds a new node at the end of list.
 * @stack: pointer to list
 * @n: data to add
 *
 * Return: (0) on success.
 */
int add_dnodeint_end(stack_t **stack, const int n)
{
	stack_t *new, *temp = *stack;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
		return (1);

	new->n = n;
	new->prev = NULL;
	new->next = NULL;

	if (*stack == NULL)
	{
		*stack = new;
		return (0);
	}

	while (temp->next != NULL)
		temp = temp->next;

	temp->next = new;
	new->prev = temp;

	return (0);
}
