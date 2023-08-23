#include "monty.h"

/**
 * fileName - identifies the name of a file from a given path
 * @pathname: file's path
 *
 * Return: name of the file.
 */
char *fileName(char *pathname)
{
	char *name = strrchr(pathname, '/');

	if (name == NULL)
		name = pathname;
	else
		name++;
	return (name);
}

/**
 * read_file - opens a file in given path, reads and execute instructions
 * @pathname: path to file
 *
 * Return: nothing.
 */
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
