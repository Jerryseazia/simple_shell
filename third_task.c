#include "header.h"
/**
 * parse_args - memory
 * @line: line parameter
 * Return: 1 if positive
 */

char **parse_args(char *line)
{
	char **args = malloc(MAXIMUM_ARGS * sizeof(char *));
	char *arg = strtok(line, " \t\n");
	int i = 0;

	while (arg != NULL && i < MAXIMUM_ARGS - 1)
	{
		args[i++] = arg;
		arg = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}
/**
 * run_command - excute passed function
 * @args: passed parameter
 */

void run_command(char **args)
{
	char *path_env = getenv("PATH");

	if (path_env == NULL)
	{
		fprintf(stderr, "PATH environment variable not set\n");
		return;
	}
	char *path = strdup(path_env);
	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		char cmd_path[MAX_PATHS];

		snprintf(cmd_path, MAX_PATHS, "%s/%s", dir, args[0]);

		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, args, NULL);
			fprintf(stderr, "execve failed\n");
			exit(EXIT_FAILURE);
		}
		dir = strtok(NULL, ":");
	}
	fprintf(stderr, "%s: command not found\n", args[0]);
	free(path);
}
/**
 * main - main function
 * Return: value for excution
 */
int main(void)
{
	char line[1024];

	while (1)
	{
		printf("ReyJ$ ");
		if (fgets(line, sizeof(line), stdin) == NULL)
		{
			break;
		}
		char **args = parse_args(line);

		if (args[0] != NULL)
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				run_command(args);
				exit(EXIT_SUCCESS);
			}
			else
			{
				wait(NULL);
			}
		}
		free(args);
	}
	return (0);
}
