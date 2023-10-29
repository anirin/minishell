/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:41:52 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 21:02:18 by atokamot         ###   ########.fr       */
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

static void	handle_child_process(int **pipefds, t_list **env_list,
		t_parsed_token *token, int check, int *finish_status, int cmd_index)
{
	if (redirect(pipefds, token, cmd_index) == false)
		exit(1);
	if (token->cmd == NULL)
		exit(0);
	if (check != BT_NOTBUILTIN)
		exec_builtin_in_child_process(env_list, check, token, finish_status);

	else
		exec_not_builtin_in_child(token, env_list);
}

static void	handle_parent_process(int check, t_parsed_token *token,
		t_list **env_list, int **pipefds, int cmd_index)
{
	char	*path;

	if (check == BT_NOTBUILTIN)
	{
		path = get_path(token->cmd, *env_list, PARENT);
		if (path != NULL)
		{
			update_env_end(path, env_list);
			free(path);
		}
	}
	close_pipefds(pipefds, cmd_index);
}

void	exec_one_cmd(int *pids, int **pipefds, t_list *parsed_tokens,
		int cmd_index, t_list **env_list, int *finish_status)
{
	t_parsed_token	*token;
	int				check;

	*finish_status = 0;
	token = (t_parsed_token *)parsed_tokens->content;
	check = is_builtin(token->cmd);
	pids[cmd_index] = -1;
	if (check != BT_NOTBUILTIN && !parsed_tokens->next && !cmd_index)
		handle_builtin(env_list, check, token, finish_status);
	else
	{
		if (parsed_tokens->next)
			pipe(pipefds[cmd_index]);
		pids[cmd_index] = fork();
		if (pids[cmd_index] == 0)
			handle_child_process(pipefds, env_list, token, check, finish_status,
				cmd_index);
		else
			handle_parent_process(check, token, env_list, pipefds, cmd_index);
	}
}
