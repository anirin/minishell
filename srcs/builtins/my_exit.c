/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:51:22 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 10:13:25 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

static void	handle_valid_exit_status(t_token *exit_status_token)
{
	int	exit_status;

	exit_status = ft_atoi(exit_status_token->token_content) % 256;
	printf("exit\n");
	if (is_under_long_max(exit_status_token->token_content) == OK
		&& is_numeric(exit_status_token->token_content) == OK)
		exit(exit_status);
	else
	{
		printf("minishell: exit: %s: numeric argument required\n",
			exit_status_token->token_content);
		exit(255);
	}
}

void	my_exit(t_list *env_list, t_list *cmd, t_list *args, int *finish_status)
{
	t_token	*exit_status_token;
	t_list	*tmp;

	(void)env_list;
	tmp = ft_lstlast(cmd);
	ft_lstadd_back(&cmd, args);
	if (!cmd->next
		|| !is_numeric(((t_token *)cmd->next->content)->token_content))
	{
		tmp->next = NULL;
		printf("exit\n");
		exit(0);
	}
	exit_status_token = (t_token *)cmd->next->content;
	tmp->next = NULL;
	if (cmd->next->next)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		*finish_status = 1;
		return ;
	}
	handle_valid_exit_status(exit_status_token);
}
