#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	///int	sign;
	int	fd[2];
	char buffer[42];
	pid_t pid;

	if (pipe(fd) == -1)
	{
		printf("pipe error\n");
		exit (1);
	}
	printf("fd[0]: %d, fd[1]: %d\n", fd[0], fd[1]); //프로그램 카운터 (PC)
	pid = fork();
	if (pid == -1)
	{
		printf("fork error\n");
		exit(1);
	}
	else if (pid == 0)
	{
		char *line = "hello mom\n";
		write(fd[1], line, strlen(line));
		// close(fd[0]);
		// sleep(4);
		// read(fd[0], buffer, 42);
		//write(1, "i am a child\n", 25);
		printf("output of child process: %s\n\n", buffer); //컨텍스트 스위칭 : 어찌됐든 프로세스를 동시에 띄우면서 생기는 문제
		exit(0);
	}
	else
	{
		// close(fd[1]);
		// printf("i am parent: \n");
		// write(1, "i am parent:\n", 13);
		//buffer[0] = '\0';
		read(fd[0], &buffer, 42);
		printf("Output of parent process : %s\n\n", buffer);
		// sleep(4);
		//write(1, "i send my message to my child", 100);
		// write(fd[1], "good job\n", 25);
		// sleep(2);
	}
	return 0;
}