/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/09/21 17:56:06 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void print_list(t_list *list)
{
	int i;

	i = 1;
	if (list == NULL)
		return ;
	while(1)
	{
		if (list->next == NULL)
		{
			printf("%d : [%s]=[%s]\n", i, (char *)list->env_name, (char *)list->env_value);
			break;
		}
		printf("%d : [%s]=[%s]\n", i, (char *)list->env_name, (char *)list->env_value);
		list = list->next;
		i++;
	}
}