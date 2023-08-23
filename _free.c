#include "monty.h"

/**
 * free_list - frees the previously allocated memory for the list
 * @stack: pointer to stack
 */
void free_list(stack_t *stack)
{
	stack_t *temp, *current = stack;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	stack = NULL;
}

/**
 * free_array - frees previously allocated memory for array of strings
 * @array: pointer to array
 */
void free_array(char **array)
{
	int i = 0;

	if (array != NULL)
	{
		for (; array[i] != NULL; i++)
			free(array[i]);
		free(array);
		array = NULL;
	}
}
