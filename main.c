#include "monty.h"

/**
 *
 */
int main(int argv, char **argc)
{
	if (argv != 2)
	{
		perror("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	head = malloc(sizeof(stack_t));
	readfile(argc[1]);
	return (0);
}

/**
 * readfile - read a file line by line
 * @filename: the name of the file
 */
void readfile(char *filename)
{
	FILE *file = fopen(filename, "r");
	int num_tok;
	char line[1024];
	char *tmp_1;
	char **args;
	unsigned int  n = 1;
	instruction_t tmp;

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file))
	{
		tmp_1 = remove_leading_space(line);
		args = tokenize(tmp_1, &num_tok);
		tmp = get_function(args);
		if (tmp == NULL)
		{
			fprintf(stderr,"L%u: unknown instruction %s", n, tmp.opcode);
			exit(EXIT_FAILURE);
		}
		tmp.f(head, n);
		n++;
	}
}

/**
 * remove_leading_space - it remove the leading space from the string
 * @line: the string
 * Return: new string without leadingspace
 */
char *remove_leading_space(char *line)
{
	size_t len;
	char *result;
	if (line == NULL)
		return (NULL);
	while (isspace(*line))
		line++;
	len = strlen(line);
	result = malloc(len + 1);

	if (result == NULL)
		return (NULL);
	strcpy(result, line);
	return (result);
}

char **tokenize(const char *input, int *tokenCount) {
	if (input == NULL)
	{
		return (NULL);
	}

	char **tokens = NULL;
	char *token;
	const char *delimiter = " ";
	int count = 0;
	int capacity = 10;

	char *inputCopy = strdup(input);
	if (inputCopy == NULL)
	{
		return (NULL);
	}
	token = strtok(inputCopy, delimiter);
	while (token != NULL)
	{
		if (count == capacity)
		{
			capacity *= 2;
			char **newTokens = (char **)malloc(capacity * sizeof(char *));
		if (newTokens == NULL)
		{
			free(inputCopy);
			return (NULL);
		}
		memcpy(newTokens, tokens, count * sizeof(char *));
		free(tokens);
		tokens = newTokens;
		}
		tokens[count] = strdup(token);
		if (tokens[count] == NULL)
		{
			free(inputCopy);
			return NULL;
		}
		count++;
		token = strtok(NULL, delimiter);
	}

	free(inputCopy);

	*tokenCount = count;
	return tokens;
}
