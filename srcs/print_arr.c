#include "libft.h"
#include "main.h"

void print_arr(char **arr)
{
	int i;
	FILE *fd;

	fd = fopen("outfile.txt", "a");
	i = 0;
	fprintf(fd, "--print arr--\n");
	printf("--print arr--\n");
	while(arr[i] != NULL)
	{
		fprintf(fd, "%d : [%s]\n", i, arr[i]);
		printf("%d : [%s]\n", i, arr[i]);
		i++;
	}
	fclose(fd);
}