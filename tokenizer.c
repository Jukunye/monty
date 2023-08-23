#include "monty.h"

/**
 * count_tokens - calculates the number of tokens in a string based on delim
 * @str: pointer to string
 *
 * Return: number of tokens found
 */
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

/**
 * tokenize - splits a given string into tokens based on delimeter
 * @line: pointer to string to parse
 *
 * Return: an array of strings, otherwise NULL
 */
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
