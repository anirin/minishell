/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:41:52 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/16 14:22:43 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

void	redirect_pipe(int **pipefds, int cmd_index)
{
	if (pipefds[cmd_index] != NULL)
	{
		close(pipefds[cmd_index][0]);
		dup2(pipefds[cmd_index][1], STDOUT_FILENO);
	}
	if (cmd_index - 1 >= 0)
		dup2(pipefds[cmd_index - 1][0], STDIN_FILENO);
}

void	close_pipefds(int **pipefds, int cmd_index)
{
	if (pipefds[cmd_index] != NULL)
	{
		close(pipefds[cmd_index][1]);
	}
	if (cmd_index - 1 >= 0)
	{
		close(pipefds[cmd_index - 1][0]);
	}
}

void	redirect_in(t_list *tokens)
{
	t_token	*token;
	char	*line;
	int		fd;

	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == RD_IN && token->token_content != NULL)
		{
			fd = open(token->token_content, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (token->status == RD_HEAEDOC && token->token_content != NULL)
		{
			fd = open(".heardoc", O_RDWR | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRWXG | S_IRWXO);
			while (line != NULL)
			{
				line = readline("heredoc> ");
				if (ft_strncmp(line, token->token_content,
						ft_strlen(token->token_content)) == 0)
					break ;
				ft_putendl_fd(line, fd);
				free(line);
				//もしheardocが何個もでできたならtmpファイルは別名にする必要がある
			}
			close(fd);
			open(".heardoc", O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			unlink(".heardoc");
		}
		else
		{
			ft_putendl_fd("syntax error '<' \n", STDERR_FILENO);
		}
		tokens = tokens->next;
	}
}

void	redirect_out(t_list *tokens)
{
	t_token	*token;
	int		fd;

	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == RD_OUT && token->token_content != NULL)
		{
			fd = open(token->token_content, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRWXG | S_IRWXO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (token->status == RD_APPEND && token->token_content != NULL)
		{
			fd = open(token->token_content, O_WRONLY | O_APPEND | O_CREAT,
					S_IRWXU | S_IRWXG | S_IRWXO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else
		{
			ft_putendl_fd("syntax error '>' \n", STDERR_FILENO);
		}
		tokens = tokens->next;
	}
}

char	**split_path(t_list *env_list)
{
	t_env	*env;
	char	**ret;

	ret = NULL;
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (ft_strncmp(env->name, "PATH", 5) == 0)
		{
			ret = ft_split(env->value, ':');
		}
		env_list = env_list->next;
	}
	return (ret);
}

char	*get_path(t_list *cmd_list, t_list *env_list)
{
	t_token	*token;
	char	*cmd;
	char	*ret;
	char	**paths;
	int		i;
	char	*tmp;

	if (cmd_list == NULL || env_list == NULL)
		return (NULL);
	i = 0;
	token = (t_token *)cmd_list->content;
	cmd = token->token_content;
	paths = split_path(env_list);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		while (paths[i] != NULL)
		{
			ret = ft_strjoin(paths[i], "/");
			tmp = ret;
			ret = ft_strjoin(tmp, cmd);
			free(tmp);
			i++;
			if (access(ret, X_OK) == 0)
			{
				return (ret);
			}
			free(ret);
		}
	}
	free_array(paths);
	return (NULL);
}

char	**get_argv(t_list *cmd, t_list *args)
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

static void	redirect(int **pipefds, t_parsed_token *token, int cmd_index)
{
	redirect_pipe(pipefds, cmd_index);
	redirect_in(token->less_than);
	redirect_out(token->greater_than);
}

static void	exec_builtin_in_child_process(t_list **env_list, int check, t_parsed_token *token)
{
	my_execve(env_list, check, token->cmd, token->args);
	exit(0);
}

static void	exec_notbuiltin_in_parent_process(t_parsed_token *token, t_list *env_list)
{
	char			*path;
	char			**argv;

	path = get_path(token->cmd, env_list);
	argv = get_argv(token->cmd, token->args);
	execve(path, argv, NULL);
	perror("execve");
	exit(1);
}

void	exec_one_cmd(int *pids, int **pipefds, t_list *parsed_tokens,
		int cmd_index, t_list **env_list)
{
	t_parsed_token	*token;
	int				check;

	token = (t_parsed_token *)parsed_tokens->content;
	check = is_builtin(token->cmd);
	if (check != BT_NOTBUILTIN && parsed_tokens->next == NULL && cmd_index == 0) //cd は親で実行させる必要がある
	{
		my_execve(env_list, check, token->cmd, token->args);
	}
	else
	{
		if (parsed_tokens->next != NULL) // parsed が null の時の対処してない
		{
			pipe(pipefds[cmd_index]);
		}
		pids[cmd_index] = fork();
		if (pids[cmd_index] == 0)
		{
			redirect(pipefds, token, cmd_index);
			if (check != BT_NOTBUILTIN)
				exec_builtin_in_child_process(env_list, check, token);
			else
				exec_notbuiltin_in_parent_process(token, *env_list);
		}
		else
			close_pipefds(pipefds, cmd_index);
	}
}