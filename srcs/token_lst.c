/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/09/21 17:59:15 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	print_list(t_list *lst)
{
	while (lst != NULL)
	{
		printf("token: [%s], status: [%d], ", lst->content, lst->status);
		if (lst->status == NORMAL)
			printf("token: NORMAL\n");
		else if (lst->status == SINGLE_QUOTE)
			printf("token: SINGLE_QUOTE\n");
		else if (lst->status == DOUBLE_QUOTE)
			printf("token: DOUBLE_QUOTE\n");
		else if (lst->status == DOLL)
			printf("token: DOLL\n");
		else if (lst->status == SPACE)
			printf("token: SPACE\n");
		else if (lst->status == PIPE)
			printf("token: PIPE\n");
		else if (lst->status == GREATER_THAN)
			printf("token: GREATER_THAN\n");
		else if (lst->status == LESS_THAN)
			printf("token: LESS_THAN\n");
		lst = lst->next;
	}
}

void	insort_list(t_list **lst, t_list *add_lst)
{
	t_list *tmp;

	if (add_lst == NULL)
		return ;
	tmp = (*lst)->next;
	ft_lstadd_back(lst, add_lst);
	ft_lstadd_back(lst, tmp);
}