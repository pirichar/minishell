#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *sd;
	/* TO OPEN THE DIR */
	dir = opendir("."); // here we just open our current directory
	if (dir == NULL) // if it failed to open
	{
		printf("Error! Unable to open direcyory.\n");
		exit (1);
	}
	
	/* to read the dir */
	while((sd=readdir(dir)) != NULL)
	{
		printf(">> %s\n", sd->d_name);
	}
	closedir(dir);
	return (0);
}