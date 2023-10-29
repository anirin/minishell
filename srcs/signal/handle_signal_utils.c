/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:44:47 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/27 17:46:59 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	change_finish_status(int signal_flag, int *finish_status)
{
	if (signal_flag == PARENT_SIGINT)
		*finish_status = 1;
	else if (signal_flag == PARENT_SIGQUIT)
		*finish_status = 0;
}

void	put_quit_massage(int signum)
{
	ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
}

void	quit_child_proccess(int signum)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
}
