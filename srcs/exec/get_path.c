/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:42:39 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/04 16:27:14 by hnakai           ###   ########.fr       */
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
	if (access(cmd, X_OK) == 0 && is_regular_file(cmd) == false)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*check_current_path_check(char *cmd, int flag)
{
	struct stat	st;

	if (ft_strncmp(cmd, "./", 2) != 0)
		return (NULL);
	stat(cmd, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR && flag == CHILD)
	{
		printf("minishell: %s: is a directory\n", cmd);
		exit(126);
	}
	if (access(cmd, X_OK) != 0 && flag == CHILD)
	{
		printf("minishell: %s: Permission denied\n", cmd);
		exit(126);
	}
	else
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*help_get_path(char **paths, char *cmd, int flag)
{
	char	*ret;

	ret = check_current_path_check(cmd, flag);
	if (ret != NULL)
		return (ret);
	ret = search_paths(paths, cmd);
	if (ret != NULL)
		return (ret);
	if (ret == NULL && flag == CHILD)
	{
		printf("minishell: %s: command not found\n", cmd);
		exit(127);
	}
	else
	{
		return (ret);
	}
	return (NULL);
}

char	*get_path(t_list *p_cmd_list, t_list *p_env_list, int flag)
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
	ret = help_get_path(paths, cmd, flag);
	free_array(paths);
	return (ret);
}
