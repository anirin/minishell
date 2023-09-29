/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/09/29 22:24:09 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

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
	//free addlistの先頭
}