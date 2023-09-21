#include "libft.h"
#include "main.h"

int	**count_and_exec_pipe(t_list *list)
{
	int i;
	int count;
	int **pipefds;

	i = 0;
	count = 0;
	while(list != NULL)
	{
		count++;
		list = list->next;
	}
	pipefds = malloc(sizeof(int *) * (count + 1));	
	while(i < count + 1)
	{
		pipefds[i] = malloc(sizeof(int) * 2);
		i++;
	}
	pipefds[i] = NULL;
	return (pipefds);
}