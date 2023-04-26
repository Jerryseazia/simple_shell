#include "header.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - functionof the prototype
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 * Return: void
 */
void free_args(char **args, char **front)
{
	size_t x;

	for (x = 0; args[x] || args[x + 1]; x++)
		free(args[x]);

	free(front);
}

/**
 * get_pid - function of the prototype
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process.
 *
 * Return: The current process ID or NULL.
 */
char *get_pid(void)
{
	size_t x = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[x] != ' ')
		x++;
	buffer[x] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - function of the prototype
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - function of the prototype
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 */
void variable_replacement(char **line, int *exe_ret)
{
	int j, l = 0, lenght;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				l = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				l = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (l = j + 1; old_line[l] &&
						old_line[l] != '$' &&
						old_line[l] != ' '; l++)
					;
				lenght = l - (j + 1);
				replacement = get_env_value(&old_line[j + 1], lenght);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[l]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[l]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}

