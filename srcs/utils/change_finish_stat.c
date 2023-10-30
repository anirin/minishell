/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_finish_stat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:52:52 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/27 17:58:23 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	wait_for_child_and_store_status(int *pids, int cmd_index,
		int *finish_status)
{
	int	cmd_count;
	int	status;

	cmd_count = 0;
	while (cmd_count < cmd_index)
	{
		child_signal_handler();
		if (pids[cmd_count] < 0)
			return ;
		else
			waitpid(pids[cmd_count], &status, 0);
		cmd_count++;
	}
	if (WIFEXITED(status))
		*finish_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*finish_status = WTERMSIG(status) + 128;
	else
		printf("aborted");
}
