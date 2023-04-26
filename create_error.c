#include "header.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - function of the prototype
 * @num: the numbers
 *
 * Return: The lenght of the digits
 */
int num_len(int num)
{
	unsigned int num1;
	int lenght = 1;

	if (num < 0)
	{
		lenght++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		lenght++;
		num1 /= 10;
	}

	return (lenght);
}

/**
 * _itoa - function of prototype
 * @num: The integer.
 *
 * Return: The string converted.
 */
char *_itoa(int num)
{
	char *buffer;
	int lenght = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (!buffer)
		return (NULL);

	buffer[lenght] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	lenght--;
	do {
		buffer[lenght] = (num1 % 10) + '0';
		num1 /= 10;
		lenght--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * create_error - function of the prototype
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}

