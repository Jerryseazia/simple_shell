#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_COMMAND_LENGTH 1024
int main(void)
{
char command[MAX_COMMAND_LENGTH];
while (1)
{
printf("ReyJ$ ");
if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
{
break;
}
command[strcspn(command, "\n")] = '\0';
pid_t pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execlp(command, command, (char *)NULL);
perror("exec");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
return (0);
}

