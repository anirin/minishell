/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:53:14 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/27 17:55:06 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_list(t_list *list)
{
	int	i;

	i = 1;
	if (list == NULL)
		return ;
	while (1)
	{
		if (list->next == NULL)
		{
			printf("%d : [%s]\n", i, (char *)list->content);
			break ;
		}
		printf("%d : [%s]\n", i, (char *)list->content);
		list = list->next;
		i++;
	}
}
