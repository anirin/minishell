#include "main.h"

void print_list(t_list *list)
{
	int i;

	i = 1;
	if (list == NULL)
		return ;
	while(1)
	{
		if (list->next == NULL)
		{
			printf("i = %d: [%s]\n", i, (char *)list->content);
			break;
		}
		printf("i = %d: [%s]\n", i, (char *)list->content);
		list = list->next;
		i++;
	}
}