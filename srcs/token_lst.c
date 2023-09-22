/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/09/22 21:17:40 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	insort_list(t_list **lst, t_list *add_lst)
{
	t_list *tmp;

	if (add_lst == NULL)
		return ;
	tmp = (*lst)->next;
	ft_lstadd_back(lst, add_lst);
	ft_lstadd_back(lst, tmp);
}