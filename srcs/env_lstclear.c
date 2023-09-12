/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lstclear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:18:00 by atsu              #+#    #+#             */
/*   Updated: 2023/09/12 16:00:08 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	env_lstclear(t_env_list **lst, void (*del)(void *))
{
	t_env_list	*tmp;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	while ((*lst) != NULL)
	{
		tmp = (*lst)->next;
		env_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}