#include "libft.h"
#include "main.h"

int	**malloc_pipefds(t_list *list)
{
	int i;
	int count;
	int **pipefds;

	i = 0;
	count = ft_lstsize(list);
	pipefds = malloc(sizeof(int *) * count);
	if(pipefds == NULL)
		exit(1);
	while(i < count - 1)
	{
		pipefds[i] = malloc(sizeof(int) * 2);
		i++;
	}
	pipefds[i] = NULL;
	return (pipefds);
}