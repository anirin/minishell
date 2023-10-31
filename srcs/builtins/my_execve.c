/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:19:23 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/31 20:40:37 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

static void	process_exit(t_list **env_list, t_list *cmd, t_list *args,
				int *finish_status);

static void	process_exit(t_list **env_list, t_list *cmd, t_list *args,
		int *finish_status)
{
	if (my_exit(*env_list, cmd, args, finish_status) == 1)
		*finish_status = 1;
	else
		*finish_status = 0;
}

void	my_execve(t_list **env_list, int check, t_parsed_token *token,
		int *finish_status)
{
	t_list	*cmd;
	t_list	*args;

	cmd = token->cmd;
	args = token->args;
	if (check == BT_EXIT)
		process_exit(env_list, cmd, args, finish_status);
	else
		*finish_status = 0;
	if (check == BT_EXPORT)
		my_export(env_list, args, finish_status);
	if (check == BT_ECHO)
		my_echo(*env_list, cmd, args);
	if (check == BT_ENV)
		my_env(*env_list, cmd, args);
	if (check == BT_PWD)
		my_pwd();
	if (check == BT_CD)
		my_cd(*env_list, cmd, args, finish_status);
	if (check == BT_UNSET)
		my_unset(env_list, args);
}
