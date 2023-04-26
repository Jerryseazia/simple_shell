#include "header.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - function of the prototype
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to str.
 */
int token_len(char *str, char *delim)
{
	int index = 0, lenght = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		lenght++;
		index++;
	}

	return (lenght);
}

/**
 * count_tokens - function of the prototype
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words within str.
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, lenght = 0;

	for (index = 0; *(str + index); index++)
		lenght++;

	for (index = 0; index < lenght; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - function of the prototype.
 * @line: The string.
 * @delim: The delimiter character to tokenize.
 *
 * Return: A pointer to an array .
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, k;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (k = 0; k < letters; k++)
		{
			ptr[t][k] = line[index];
			index++;
		}

		ptr[t][k] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
} /*create_divide*/

