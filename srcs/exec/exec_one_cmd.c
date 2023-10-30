/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:41:52 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/30 15:55:14 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "libft.h"
#include "main.h"

static int	handle_builtin(t_list **env_list, int check, t_parsed_token *token,
		int *finish_status)
{
	int	tmp_stdin;
	int	tmp_stdout;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	redirect_in_out(token->redirect);
	my_execve(env_list, check, token, finish_status);
	dup2(tmp_stdin, STDIN_FILENO);
	dup2(tmp_stdout, STDOUT_FILENO);
	return (1);
}

static void	handle_child_process(t_exec *data, int check, int *finish_status)
{
	if (redirect(data->pipefds, data->token, data->cmd_index) == false)
		exit(1);
	if (!data->token->cmd)
		exit(0);
	if (check != BT_NOTBUILTIN)
		exec_builtin_in_child_process(data->env_list, check, data->token,
			finish_status);
	else
		exec_not_builtin_in_child(data->token, data->env_list);
}

static void	handle_parent_process(t_exec *data, int check)
{
	char	*path;

	if (check == BT_NOTBUILTIN)
	{
		path = get_path(data->token->cmd, *data->env_list, PARENT);
		if (path)
		{
			update_env_end(path, data->env_list);
			free(path);
		}
	}
	close_pipefds(data->pipefds, data->cmd_index);
}

void	exec_one_cmd(t_exec *data, t_list *parsed_tokens, int *finish_status)
{
	int	check;

	*finish_status = 0;
	data->token = (t_parsed_token *)parsed_tokens->content;
	check = is_builtin(data->token->cmd);
	data->pids[data->cmd_index] = -1;
	if (check != BT_NOTBUILTIN && !parsed_tokens->next && !data->cmd_index)
		handle_builtin(data->env_list, check, data->token, finish_status);
	else
	{
		if (parsed_tokens->next)
			pipe(data->pipefds[data->cmd_index]);
		data->pids[data->cmd_index] = fork();
		if (data->pids[data->cmd_index] == 0)
			handle_child_process(data, check, finish_status);
		else
			handle_parent_process(data, check);
	}
}
