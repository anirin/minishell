/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:44:47 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/30 15:13:41 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	change_finish_status(int g_signal_flag, int *finish_status)
{
	if (g_signal_flag == PARENT_SIGINT)
		*finish_status = 1;
	else if (g_signal_flag == PARENT_SIGQUIT)
		*finish_status = 0;
}

void	put_quit_massage(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
}

void	quit_child_proccess(int signum)
{
	(void)signum;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
}
