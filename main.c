#include "monty.h"

void read_file(char *pathname);
char **tokens = NULL;
stack_t *head = NULL;
int queue_flag = 0;

/**
 * main - entry to the program
 * @argc: argument count
 * @argv: array of command line arguments
 *
 * Return: (0) on success
 */
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
