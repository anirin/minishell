/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/21 16:24:08 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// #include <readline/history.h>
// #include <readline/readline.h>

void	put_new_prompt(int signum);
void	quit_child_proccess(int signum);
void	nothing_to_do(int signum);
void	nothing_to_do_for_child(int signum);

void	handle_signal(void)
{
	signal(SIGINT, put_new_prompt);
	signal(SIGQUIT, nothing_to_do);
}

void	handle_signal_child_proccess(void)
{
	signal(SIGINT, quit_child_proccess);
	signal(SIGQUIT, quit_child_proccess);
}

void	put_new_prompt(int signum)
{
	g_finish_status = 1;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	nothing_to_do(int signum)
{
	g_finish_status = 0;
}

void	quit_child_proccess(int signum)
{
	g_finish_status = 127;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	nothing_to_do_for_child(int signum)
{
	printf("\n");
}
