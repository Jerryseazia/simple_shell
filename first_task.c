#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS_LENGTH 120
#define MESSAGE "ReyJ$ "

/**
 * main - function
 * Return: void
 */

int main(void)
{
	char *buffer = malloc(sizeof(char) * MAX_COMMANDS_LENGTH);

	if (!buffer)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf(MESSAGE);
		if (!fgets(buffer, MAX_COMMANDS_LENGTH, stdin))
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		buffer[strcspn(buffer, "\n")] = 0;
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(buffer, NULL, NULL) == -1)
			{
				perror("executable");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;

			if (wait(&status) == -1)
			{
				perror("wait");
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(status))
			{
				printf("Code exited with status ~  %d\n", WEXITSTATUS(status));
			}
			else if (WIFSIGNALED(status))
			{
				printf("Program was terminated by signal %d\n", WTERMSIG(status));
			}
		}
	}
	free(buffer);
	exit(EXIT_SUCCESS);
}
