/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:53:10 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/27 17:57:10 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	printf("--print arr--\n");
	while (arr[i] != NULL)
	{
		printf("%d : [%s]\n", i, arr[i]);
		i++;
	}
}
