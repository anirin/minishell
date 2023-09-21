#include "libft.h"
#include "main.h"

t_list	*parsed_lstnew(t_list *greater_than, t_list *less_than, t_list *cmd)
{
	t_list	*p;

	p = malloc(sizeof(t_list));
	if (p == NULL)
		return (NULL);
	p->greater_than = greater_than;
	p->less_than = less_than;
	p->cmd = cmd;
	p->next = NULL;
	return (p);
}

t_list	*parsed_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	parsed_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	token_lstclear(&lst->greater_than, del);
	token_lstclear(&lst->less_than, del);
	token_lstclear(&lst->cmd, del);
	free(lst);
}

void	parsed_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	while ((*lst) != NULL)
	{
		tmp = (*lst)->next;
		parsed_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

void	parsed_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = parsed_lstlast(*lst);
	if (last == NULL)
		return ;
	last->next = new;
}

void	print_list(t_list *list)
{
	int i;

	i = 1;
	if (list == NULL)
		return ;
	while (1)
	{
		if (list->next == NULL)
		{
			printf("list %d\n", i);
			print_list(list->greater_than);
			print_list(list->less_than);
			print_list(list->cmd);
			printf("\n");
			break ;
		}
		printf("list %d\n", i);
		print_list(list->greater_than);
		print_list(list->less_than);
		print_list(list->cmd);
		printf("\n");
		list = list->next;
		i++;
	}
}