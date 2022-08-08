#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#define PATH_MAX 1024

int	main(int argc, char **argv)
{

	// DIR	*dp;
	// struct dirent	*dirp;
	int i = 0;
	char name[PATH_MAX];

	while (1)
	{
		if(argc != 2)
		{
			fprintf(stderr, "Usage: %s <path name>\n", argv[0]);
			return 1;
		}
		if(i == 0 && chdir(argv[1])==-1)
		{
			printf("failed, change directory\n");
		}
		else if (i == 0)
		{
			// printf("Before Current Directory:%s\n",getcwd(name,PATH_MAX));
			printf("After Current Directory:%s\n",getcwd(name,PATH_MAX));
			// dp = opendir(getcwd(name, PATH_MAX));
			// while ((dirp = readdir(dp)) != NULL)
			// 	printf("%s\n", dirp->d_name);
			// closedir(dp);
			i = 1;
		}
	}
    return 0;
}
