/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:51:22 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/04 16:58:57 by atokamot         ###   ########.fr       */
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

static void	print_too_many_error(int *finish_status, t_list *tmp)
{
	printf("minishell: exit: too many arguments\n");
	exit(1);
}

int	my_exit_child(t_list *cmd, t_list *args, int *finish_status)
{
	t_token	*exit_status_token;
	t_list	*tmp;
	int	exit_status;

	tmp = ft_lstlast(cmd);
	ft_lstadd_back(&cmd, args);
	if (cmd->next == NULL)
	{
		exit(*finish_status);
	}
	exit_status_token = (t_token *)cmd->next->content;
	exit_status = ft_atoi(exit_status_token->token_content) % 256;
	if (is_numeric(exit_status_token->token_content) == NG
		|| is_under_long_max(exit_status_token->token_content) == NG)
		print_numeric_error(exit_status_token);
	else if (cmd->next->next != NULL)
		print_too_many_error(finish_status, tmp);
	else
		exit(exit_status);
	return (0);
}
