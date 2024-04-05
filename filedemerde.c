#include<libc.h>

int main()
{
	printf("QWERTY\n");
	int pid = fork();
	if (pid == 0)
		printf("CHILD\n");
}