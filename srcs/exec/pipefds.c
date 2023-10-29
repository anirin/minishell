/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipefds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:45:16 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 21:45:38 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

int	**malloc_pipefds(t_list *list)
{
	int	i;
	int	count;
	int	**pipefds;

	i = 0;
	count = ft_lstsize(list);
	pipefds = malloc(sizeof(int *) * count);
	while (i < count - 1)
	{
		pipefds[i] = malloc(sizeof(int) * 2);
		i++;
	}
	pipefds[i] = NULL;
	return (pipefds);
}

void	free_pipefds(int **pipefds)
{
	int	i;

	i = 0;
	while (pipefds[i] != NULL)
	{
		free(pipefds[i]);
		i++;
	}
	free(pipefds);
}
