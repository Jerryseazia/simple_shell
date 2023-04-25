#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "header.h"

/* Display the shell prompt */
void display_prompt(void)
{
printf("ReyJ ");
fflush(stdout);
}
/* Read a command line from standard input */
int read_command(char *command)
{
if (fgets(command, MAX_COMMANDS_LENGTH, stdin) == NULL)
{
return (0);
}
int length = strlen(command);
if (command[length - 1] == '\n')
{
command[length - 1] = '\0';
}
return (1);
}
/* Execute a command */
int execute_command(char *command)
{
char path[MAX_COMMANDS_LENGTH];
printf(path, MAX_COMMANDS_LENGTH, "/usr/bin/%s", command);
if (access(path, X_OK) == 0)
{
pid_t pid = fork();
if (pid == 0)
{
/* Child process */
execl(path, command, (char *)NULL);
fprintf(stderr, "Failed to execute command: %s\n", command);
exit(1);
}
else if (pid < 0)
{
 /* Error forking process */
fprintf(stderr, "Failed to fork process\n");
return (1);
}
else
{
/* Parent process */
int status;
waitpid(pid, &status, 0);
return (status);
}
}
else
{
/* Command not found */
fprintf(stderr, "Command not found: %s\n", command);
return (1);
}
}
    int main(void)
{
char command[MAX_COMMANDS_LENGTH];
while (1)
{
/* Display prompt and read command line */
display_prompt();
if (!read_command(command))
{
break;
}
/* Execute command */
int status = execute_command(command);
/* Check status */
if (status)
{
fprintf(stderr, "Command failed with status %d\n", status);
}
}
return (0);
}

