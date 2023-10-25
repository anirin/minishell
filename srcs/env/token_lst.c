/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/10/25 15:52:42 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

/*
void	insort_list(t_list *token, t_list *add_lst)
{
	t_list *next_list;
	t_token	*tmp;
	t_token	*add_tmp;

	if (add_lst == NULL)
		return ;
	tmp = (t_token *)token->content;
	add_tmp = (t_token *)add_lst->content;
	free(tmp->token_content);
	tmp->token_content = add_tmp->token_content;
	tmp->status = add_tmp->status;
	next_list = token->next;
	token->next = add_lst->next;
	ft_lstadd_back(&token, next_list);
}
*/

void	insort_list(t_list **token, t_list *add_lst, t_list *prev)
{
	t_list *tmp;
	t_list *tmp_next;
	t_list *tmp_next_next;

	if (prev != NULL)
	{
		tmp = prev->next;
		tmp_next_next = prev->next->next;
		prev->next = add_lst;
		ft_lstadd_back(&prev, tmp_next_next);
		ft_lstdelone(tmp, (void *)free_token);
	}
	else //if (prev == NULL)
	{
		tmp = (*token);
		tmp_next = (*token)->next;
		(*token) = add_lst;
		ft_lstadd_back(&add_lst, tmp_next);
		ft_lstdelone(tmp, (void *)free_token);
	}
}