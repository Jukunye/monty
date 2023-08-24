#include "monty.h"

/**
  * open_file - Opens a file to interpret the commands within
  * @filename: The file to be opened
  *
  * Return: The file descriptor of the opened file
  */
FILE *open_file(char *filename)
{
	FILE *fd = NULL;

	check_access_rights(filename);

	fd = fopen(filename, "r");

	if (!fd)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	return (fd);
}
