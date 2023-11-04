/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:51:22 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/04 17:29:21 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

static void	print_numeric_error(t_token *exit_status_token)
{
	printf("minishell: exit: %s: numeric argument required\n",
		exit_status_token->token_content);
	exit(255);
}

static int	print_too_many_error(int *finish_status, t_list *tmp)
{
	printf("exit\nminishell: exit: too many arguments\n");
	*finish_status = 1;
	tmp->next = NULL;
	return (1);
}

int	my_exit(t_list *cmd, t_list *args, int *finish_status)
{
	t_token	*exit_status_token;
	t_list	*tmp;
	int		exit_status;

	tmp = ft_lstlast(cmd);
	ft_lstadd_back(&cmd, args);
	if (cmd->next == NULL)
	{
		printf("exit\n");
		exit(*finish_status);
	}
	exit_status_token = (t_token *)cmd->next->content;
	exit_status = ft_atoi(exit_status_token->token_content) % 256;
	if (is_numeric(exit_status_token->token_content) == NG
		|| is_under_long_max(exit_status_token->token_content) == NG)
		print_numeric_error(exit_status_token);
	else if (cmd->next->next != NULL)
		return (print_too_many_error(finish_status, tmp));
	else
	{
		printf("exit\n");
		exit(exit_status);
	}
	return (0);
}
