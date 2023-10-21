/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/21 15:58:39 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// #include <readline/history.h>
// #include <readline/readline.h>

void	put_new_prompt(int signum, siginfo_t *siginfo, void *shell_list);
void	quit_child_proccess(int signum);
void	nothing_to_do(int signum);
void	nothing_to_do_for_child(int signum);

void	handle_signal()
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = put_new_prompt;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, nothing_to_do);
}

void	put_new_prompt(int signum, siginfo_t *siginfo, void *content)
{
	g_finish_status = 1;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit_child_proccess(int signum)
{
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
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
	;
}
