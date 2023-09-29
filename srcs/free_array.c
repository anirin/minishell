#include "libft.h"
#include "main.h"

void	free_array(char **array)
{
	while(*array != NULL)
	{
		free(*array);
		array++;
	}
	free(array);
}