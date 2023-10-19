/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_program.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/19 21:35:42 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <readline/history.h>
#include <readline/readline.h>

bool	signal_received = false;

void	put_new_prompt(int signum);
void	nothing_to_do(int signum);

bool	check_signal(void)
{
	signal_received = false;
	signal(SIGINT, put_new_prompt);
	signal(SIGQUIT, nothing_to_do);
	return (signal_received);
}

void	put_new_prompt(int signum)
{
	signal_received = true;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	nothing_to_do(int signum)
{
	;
}
