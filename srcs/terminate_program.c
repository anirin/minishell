/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_program.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/03 22:46:05 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = terminate_program;
	sigaction(SIGINT, &sa, NULL);
}

void	terminate_program(int signum, siginfo_t *pid, void *context)
{
	(void)pid;
	(void)context;

	printf("%d\n", pid->si_pid);
	kill(pid->si_pid, SIGUSR1);
}
