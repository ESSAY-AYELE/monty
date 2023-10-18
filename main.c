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
 *
 */
void readfile(char *filename)
{
	FILE *file = fopen(filename, "r");
	char line[1024];
	char *tmp;
	char **args;
	int  n = 1;
	instruction_t *instruction;

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file))
	{
		tmp = remove_leading_space(line);
		args = tokenize(tmp);
	
