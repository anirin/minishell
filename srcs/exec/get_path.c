/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:42:39 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 20:31:54 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

static char	**split_path(t_list *env_list)
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

static char	*check_cmd_directory(char *cmd)
{
	struct stat	st;

	stat(cmd, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
	{
		printf("minishell: %s: is a directory\n", cmd);
		exit(126);
	}
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_paths(char **paths, char *cmd)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	while (paths && paths[i])
	{
		ret = ft_strjoin(paths[i], "/");
		tmp = ret;
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(ret, X_OK) == 0)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}

static char	*help_get_path(char **paths, char *cmd)
{
	char	*ret;

	ret = search_paths(paths, cmd);
	if (!ret)
	{
		printf("minishell: %s: command not found\n", cmd);
		exit(127);
	}
	else
	{
		return (ret);
	}
}

char	*get_path(t_list *p_cmd_list, t_list *p_env_list)
{
	t_token	*token;
	char	*cmd;
	char	**paths;
	char	*ret;

	if (!p_cmd_list || !p_env_list)
		return (NULL);
	token = (t_token *)p_cmd_list->content;
	cmd = token->token_content;
	paths = split_path(p_env_list);
	ret = check_cmd_directory(cmd);
	if (ret != NULL)
	{
		free_array(paths);
		return (ret);
	}
	if (!paths && access(cmd, F_OK) == 0)
	{
		perror("minishell: ");
		exit(126);
	}
	ret = help_get_path(paths, cmd);
	free_array(paths);
	return (ret);
}
