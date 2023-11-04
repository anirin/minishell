/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_in_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:01:00 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/04 17:03:03 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "libft.h"
#include "main.h"

static char	**get_argv(t_list *cmd, t_list *args)
{
	t_token	*token;
	char	**ret;
	int		i;

	i = 0;
	ft_lstadd_back(&cmd, args);
	ret = malloc(sizeof(char *) * (ft_lstsize(cmd) + 1));
	while (cmd != NULL)
	{
		token = (t_token *)cmd->content;
		ret[i++] = ft_strdup(token->token_content);
		cmd = cmd->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	exec_builtin_in_child_process(t_list **env_list, int check,
		t_parsed_token *token, int *finish_status)
{
	if (check == BT_EXIT)
		my_exit_child(token->cmd, token->args, finish_status);
	else if (check)
		my_execve(env_list, check, token, finish_status);
	exit(0);
}

void	exec_not_builtin_in_child(t_parsed_token *token, t_list **env_list)
{
	char	*path;
	char	**argv;
	char	**envp;

	path = get_path(token->cmd, *env_list, CHILD);
	argv = get_argv(token->cmd, token->args);
	envp = envlist_to_envp(*env_list);
	execve(path, argv, envp);
	perror("execve");
	exit(1);
}
