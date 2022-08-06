#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#define PATH_MAX 1024

int	main(void)
{
	char	*str;
	pid_t	pid;
	char name[PATH_MAX];

	while (1)
	{

		str = readline(getcwd(name, PATH_MAX));
		if (strncmp(str, "cd /", 4) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve("../chdir/cd", &str, NULL);
		}
		else if (strncmp(str, "pwd", 2) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve("/bin/pwd", &str, NULL);
		}
		else
			printf("%s\n", str);
	}
	return (0);
}