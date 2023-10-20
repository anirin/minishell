/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/20 16:32:47 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// #include <readline/history.h>
// #include <readline/readline.h>

void	put_new_prompt(int signum);
void	quit_child_proccess(int signum);
void	nothing_to_do(int signum);
void	nothing_to_do_for_child(int signum);

void	handle_signal(t_list *shell_list)
{
	signal(SIGINT, put_new_prompt);
	modify_finish_status(shell_list, 1);
	signal(SIGQUIT, nothing_to_do);
}

void	put_new_prompt(int signum)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit_child_proccess(int signum)
{
	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

void	handle_signal_for_child(void)
{
	signal(SIGINT, nothing_to_do_for_child);
	signal(SIGQUIT, quit_child_proccess);
}

void	nothing_to_do_for_child(int signum)
{
	printf("\n");
}

void	nothing_to_do(int signum)
{
	rl_on_new_line();
}
