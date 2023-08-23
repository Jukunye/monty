#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

extern char **tokens;

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* Prototypes */
char *fileName(char *pathname);
void read_file(char *pathname);
int count_tokens(char *str);
char **tokenize(char *line);
void free_array(char **array);
void operations(stack_t **stack, unsigned int line_number);
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
int pop_int(stack_t **stack);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);
void sub(stack_t **stack, unsigned int line_number);
void mul(stack_t **stack, unsigned int line_number);
void mod(stack_t **stack, unsigned int line_number);
int add_dnodeint(stack_t **stack, const int n);
void free_list(stack_t *stack);

char **tokens = NULL;

int main(int argc, char **argv)
{
	char *pathname = argv[1];

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	read_file(pathname);

	return (0);
}

char *fileName(char *pathname)
{
	char *name = strrchr(pathname, '/');

	if (name == NULL)
		name = pathname;
	else
		name++;
	return (name);
}
void read_file(char *pathname)
{
	FILE *byteCodes;
	char *lineptr = NULL;
	stack_t *stack = NULL;
	size_t n = 0, line_number = 0;
	ssize_t nread;

	byteCodes = fopen(pathname, "r");
	if (byteCodes == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", fileName(pathname));
		exit(EXIT_FAILURE);
	}
	while ((nread = getline(&lineptr, &n, byteCodes)) != -1)
	{
		line_number++;
		tokens = tokenize(lineptr);
		if (tokens == NULL)
		{
			free_array(tokens);
			continue;
		}
		operations(&stack, line_number);
		free_array(tokens);
	}
	free(lineptr);
	free_list(stack);

	fclose(byteCodes);
}
int count_tokens(char *str)
{
	char *delim = " \t\n";
	int i = 0, count = 0, in_token = 0;

	for (; str[i] != '\0'; i++)
	{
		if (strchr(delim, str[i]) != NULL)
		{
			in_token = 0;
		}
		else if (!in_token)
		{
			in_token = 1;
			count++;
		}
	}
	free(str);
	return (count);
}
char **tokenize(char *line)
{
	char **tokens;
	char *lineCopy, *token;
	char *delim = " \n\t";
	int i, tokenCount;

	if (line == NULL)
		return (NULL);

	lineCopy = strdup(line);
	tokenCount = count_tokens(lineCopy);
	if (tokenCount == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (tokenCount + 1));
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, delim);
	i = 0;
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	tokens[i] = NULL;

	return (tokens);
}

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
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
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
void push(stack_t **stack, unsigned int line_number)
{
	char *endptr;
	int n = strtol(tokens[1], &endptr, 10);

	if (*endptr != '\0')
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		free_array(tokens);
		free_list(*stack);
		exit(EXIT_FAILURE);
	}
	if (add_dnodeint(stack, n))
	{
		fprintf(stderr, "Memory allocation: Failed\n");
		free_array(tokens);
		free_list(*stack);
		exit(EXIT_FAILURE);
	}
}
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
void add(stack_t **stack, unsigned int line_number)
{
	int i, tos, tos1;
	stack_t *temp = *stack;

	if (temp == NULL || temp->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_SUCCESS);
	}

	tos = pop_int(stack);
	tos1 = pop_int(stack);

	tos += tos1;

	i = add_dnodeint(stack, tos);

	(void)i;
}
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
void mul(stack_t **stack, unsigned int line_number)
{
	int i, tos, tos1;
	stack_t *temp = *stack;

	if (temp == NULL || temp->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		free_list(*stack);
		free_array(tokens);
		exit(EXIT_SUCCESS);
	}

	tos = pop_int(stack);
	tos1 = pop_int(stack);

	tos1 *= tos;

	i = add_dnodeint(stack, tos1);

	(void)i;
}
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
