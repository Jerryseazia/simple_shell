#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_COMMAND_LENGTH 1024
int main(void)
{
char command[MAX_COMMAND_LENGTH];
while (1)
{
printf("ReyJ$ ");
fgets(command, MAX_COMMAND_LENGTH, stdin);
command[strcspn(command, "\n")] = '\0';
if (strcmp(command, "exit") == 0)
{
break;
}
system(command);
}
return (0);
}

