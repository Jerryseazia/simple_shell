#include "header.h"
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
        char *tokens[MAX_COMMANDS_LENGTH];
        int num_tokens = 0;
        char *token = strtok(buffer, " ");

        while (token != NULL)
        {
            tokens[num_tokens] = token;
            num_tokens++;
            token = strtok(NULL, " ");
        }
        if (num_tokens == 0)
        {

            continue;
        }
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process*/
            char *args[num_tokens + 1];

            for (int i = 0; i < num_tokens; i++)
            {
                args[i] = tokens[i];
            }
            args[num_tokens] = NULL;

            if (execvp(args[0], args) == -1)
            {
                perror("execvp");
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
                printf("Program exited with status %d\n", WEXITSTATUS(status));
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

