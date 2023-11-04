/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:53:14 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/11/04 16:15:33 by atokamot         ###   ########.fr       */
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
