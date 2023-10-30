/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:19:23 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 10:31:35 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

void	my_execve(t_list **env_list, int check, t_parsed_token *token,
		int *finish_status)
{
	t_list	*cmd;
	t_list	*args;

	cmd = token->cmd;
	args = token->args;
	if (check == BT_EXPORT)
		my_export(env_list, args, finish_status);
	if (check == BT_ECHO)
		my_echo(*env_list, cmd, args);
	if (check == BT_ENV)
		my_env(*env_list, cmd, args);
	if (check == BT_EXIT)
		my_exit(*env_list, cmd, args, finish_status);
	if (check == BT_PWD)
		my_pwd();
	if (check == BT_CD)
		my_cd(*env_list, cmd, args, finish_status);
	if (check == BT_UNSET)
		my_unset(env_list, args);
	return ;
}
