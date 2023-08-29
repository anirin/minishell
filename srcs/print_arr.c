#include "libft.h"
#include "main.h"

void print_arr(char **arr)
{
	int i;

	i = 0;
	printf("--print arr--\n");
	while(arr[i] != NULL)
	{
		printf("%d : [%s]\n", i, arr[i]);
		i++;
	}
}