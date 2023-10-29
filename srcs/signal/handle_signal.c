/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/29 21:17:16 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_new_prompt(int signum);
void	put_quit_massage(int signum);
void	nothing_to_do(int signum);
void	quit_child_proccess(int signum);

void	parent_signal_handler(int *finish_status)
{
	(void)finish_status;
	signal(SIGINT, put_new_prompt);
	signal(SIGQUIT, nothing_to_do);
}

void	child_signal_handler(void)
{
	signal(SIGINT, quit_child_proccess);
	signal(SIGQUIT, put_quit_massage);
}

void	put_new_prompt(int signum)
{
	(void)signum;
	signal_flag = PARENT_SIGINT;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	nothing_to_do(int signum)
{
	(void)signum;
	signal_flag = PARENT_SIGQUIT;
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}
