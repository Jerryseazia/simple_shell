#include "header.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - function of the prototype
 * @args: An array of arguments passed.
 * Return: The error
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int lenght;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	lenght = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (lenght + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - function of the prototype
 * @args: An array of arguments passed.
 *
 * Return: The error.
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int lenght;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	lenght = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (lenght + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}

