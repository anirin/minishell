#include "main.h"

void print_env_list(t_env_list *list)
{
	int i;

	i = 1;
	if (list == NULL)
		return ;
	while(1)
	{
		if (list->next == NULL)
		{
			printf("%d : [%s]=[%s]\n", i, (char *)list->env_name, (char *)list->env_value);
			break;
		}
		printf("%d : [%s]=[%s]\n", i, (char *)list->env_name, (char *)list->env_value);
		list = list->next;
		i++;
	}
}