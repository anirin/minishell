/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/10/29 21:35:16 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_env.h"
#include "libft.h"
#include "main.h"

void	insort_list(t_list **token, t_list *add_lst, t_list *prev)
{
	t_list	*tmp;
	t_list	*tmp_next;
	t_list	*tmp_next_next;

	if (prev != NULL)
	{
		tmp = prev->next;
		tmp_next_next = prev->next->next;
		prev->next = add_lst;
		ft_lstadd_back(&prev, tmp_next_next);
		ft_lstdelone(tmp, (void *)free_token);
	}
	else
	{
		tmp = (*token);
		tmp_next = (*token)->next;
		(*token) = add_lst;
		ft_lstadd_back(&add_lst, tmp_next);
		ft_lstdelone(tmp, (void *)free_token);
	}
}
