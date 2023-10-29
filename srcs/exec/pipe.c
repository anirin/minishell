/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:44:02 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 20:22:28 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

void	redirect_pipe(int **pipefds, int cmd_index)
{
	if (pipefds[cmd_index] != NULL)
	{
		close(pipefds[cmd_index][0]);
		dup2(pipefds[cmd_index][1], STDOUT_FILENO);
	}
	if (cmd_index - 1 >= 0)
		dup2(pipefds[cmd_index - 1][0], STDIN_FILENO);
}

void	close_pipefds(int **pipefds, int cmd_index)
{
	if (pipefds[cmd_index] != NULL)
	{
		close(pipefds[cmd_index][1]);
	}
	if (cmd_index - 1 >= 0)
	{
		close(pipefds[cmd_index - 1][0]);
	}
}
