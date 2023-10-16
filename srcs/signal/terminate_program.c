/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_program.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:08:15 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/16 17:57:14 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <readline/readline.h>
#include <readline/history.h>

bool	signal_received = false;

void	signal_handler(int signum);

bool	is_signal_received(void)
{
	signal_received = false;
	signal(SIGINT, signal_handler);
	return (signal_received);
}

void	signal_handler(int signum)
{
	signal_received = true;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
