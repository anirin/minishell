/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:23:31 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 20:32:24 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

int			signal_flag = 0;

static void	add_history_and_free(char *line, t_list *tokens,
		t_list *parsed_tokens)
{
	add_history(line);
	ft_lstclear(&tokens, (void *)free_token);
	ft_lstclear(&parsed_tokens, (void *)free_parsed_token);
	free(line);
}

static void	exec_cmd(t_list *parsed_tokens, t_list **env_list,
		int *finish_status)
{
	int		*pids;
	int		**pipefds;
	t_list	*tmp;
	int		cmd_index;

	cmd_index = 0;
	pids = malloc(sizeof(int) * ft_lstsize(parsed_tokens));
	pipefds = malloc_pipefds(parsed_tokens);
	tmp = parsed_tokens;
	while (tmp != NULL)
	{
		exec_one_cmd(pids, pipefds, tmp, cmd_index, env_list, finish_status);
		cmd_index++;
		tmp = tmp->next;
	}
	free_pipefds(pipefds);
	wait_for_child_and_store_status(pids, cmd_index, finish_status);
	free(pids);
}

static int	exec_one_line(t_list **env_list, int *finish_status)
{
	t_list	*tokens;
	t_list	*parsed_tokens;
	char	*line;

	signal_flag = -1;
	parent_signal_handler(finish_status);
	line = readline("\033[32m$>\033[0m ");
	change_finish_status(signal_flag, finish_status);
	if (line == NULL)
	{
		line = ft_strdup("exit");
	}
	tokens = lexer(line);
	parsed_tokens = parser(&tokens, *env_list, finish_status);
	if (parsed_tokens == NULL || check_syntax_error(parsed_tokens, tokens,
			finish_status) == NG)
	{
		add_history_and_free(line, tokens, parsed_tokens);
		return (-1);
	}
	exec_cmd(parsed_tokens, env_list, finish_status);
	add_history_and_free(line, tokens, parsed_tokens);
	return (0);
}

int	minishell(char **envp)
{
	t_list	*env_list;
	int		finish_status[2];

	finish_status[0] = 0;
	signal_flag = -1;
	env_list = envp_convert_to_envlist(envp);
	while (1)
	{
		if (exec_one_line(&env_list, finish_status) == -1)
			continue ;

	}
	ft_lstclear(&env_list, (void *)free_env);
	free(finish_status);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
}
