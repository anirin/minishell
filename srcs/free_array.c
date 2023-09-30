#include "libft.h"
#include "main.h"

void	free_array(char **array)
{
	int i;

	i = 0;
	while(array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}