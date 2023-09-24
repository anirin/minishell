/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/09/24 21:42:26 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	insort_list(t_list *token, t_list *add_lst)
{
	t_list *next_list;
	t_list *last;
	t_token	*tmp;
	t_token	*add_tmp;

	if (add_lst == NULL)
		return ;
	tmp = (t_token *)token->content;
	add_tmp = (t_token *)add_lst->content;
	tmp->token_content = add_tmp->token_content;
	tmp->status = add_tmp->status;
	next_list = token->next;
	token->next = add_lst->next;
	last = ft_lstlast(add_lst);	
	last->next = next_list;
}