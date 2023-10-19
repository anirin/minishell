/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accept_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/20 02:37:55 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// #include <readline/history.h>
// #include <readline/readline.h>

void	put_new_prompt(int signum);
void	nothing_to_do(int signum);
void	nothing_to_do_for_child(int signum);

void	handle_signal(void)
{
	signal(SIGINT, put_new_prompt);
	signal(SIGQUIT, nothing_to_do_for_child);
}

void	put_new_prompt(int signum)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	nothing_to_do(int signum)
{
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

void	check_signal_for_child(int pids)
{
	kill(pids, SIGINT);
	signal(SIGINT, nothing_to_do_for_child);
	signal(SIGQUIT,  nothing_to_do);
}

void	nothing_to_do_for_child(int signum)
{
	printf("\n");
}
