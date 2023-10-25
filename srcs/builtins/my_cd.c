/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/23 22:38:54 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	is_accessible(char *input_path);
bool	is_directory(char *input_path);
char	*get_env_value(t_list *env_list, char *value_name, int cmd_index);
char	*get_oldpwd(t_list *env_list, t_list *cmd, int *finish_status);
char	*get_homedir(t_list *env_list, int *finish_status);

void	my_cd(t_list *env_list, t_list *cmd, t_list *args, int *finish_status)
{
	char	*new_path;
	t_token	*args_content;

	if (args == NULL)
	{
		if (cmd != NULL && cmd->next != NULL)
			new_path = get_oldpwd(env_list, cmd,finish_status);
		else
			new_path = get_homedir(env_list,finish_status);
	}
	else
	{
		args_content = (t_token *)args->content;
		new_path = ft_strdup(args_content->token_content);
	}
	if (overwrite_oldpwd(env_list) != SUCCESS)
	{
		// chdir("/Users/nakaiheizou/tmp/tmp1/..");
		return ;
	}
	if (new_path == NULL || ft_strncmp(new_path, "", 1) == 0)
		return ;
	if (is_directory(new_path) == false || is_accessible(new_path) == false)
	{
		*finish_status = 1;
		return ;
	}
	chdir(new_path);
	free(new_path);
	if (overwrite_pwd(env_list) != SUCCESS)
		return ;
}

int	overwrite_pwd(t_list *env_list)
{
	int		env_index;
	char	*crt_path;

	crt_path = getcwd(NULL, 0);
	if (crt_path == NULL)
	{
		ft_putstr_fd("cd : error retrieving current directory: getcwd: cannot access parent directories",
			STDERR_FILENO);
		perror(":");
		return (FAIL);
	}
	env_index = is_added_env("PWD", env_list);
	if (env_index == -1)
	{
		free(crt_path);
		return (SUCCESS);
	}
	overwrite_env(env_index, crt_path, env_list);
	free(crt_path);
	return (SUCCESS);
}

int	overwrite_oldpwd(t_list *env_list)
{
	int		env_index;
	char	*crt_path;

	crt_path = getcwd(NULL, 0);
	if (crt_path == NULL)
	{
		ft_putstr_fd("cd : error retrieving current directory: getcwd: cannot access parent directories",
			STDERR_FILENO);
		perror("");
		return (FAIL);
	}
	env_index = is_added_env("OLDPWD", env_list);
	if (env_index == -1)
	{
		free(crt_path);
		return (SUCCESS);
	}
	overwrite_env(env_index, crt_path, env_list);
	free(crt_path);
	return (SUCCESS);
}

bool	is_accessible(char *input_path)
{
	if (access(input_path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: cd", STDERR_FILENO);
		perror("");
		return (false);
	}
	else
		return (true);
}

bool	is_directory(char *input_path)
{
	struct stat	*stat_info;

	stat_info = (struct stat *)malloc(sizeof(struct stat) * 1);
	if (stat_info == NULL)
		exit(1);
	if (stat(input_path, stat_info) != 0)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: cd:", STDERR_FILENO);
			perror("");
		}
		free((void *)stat_info);
		return (false);
	}
	if ((stat_info->st_mode & S_IFMT) != S_IFDIR)
	{
		ft_putstr_fd("minishell: cd:", STDERR_FILENO);
		perror("");
		free((void *)stat_info);
		return (false);
	}
	else
	{
		free((void *)stat_info);
		return (true);
	}
}

char	*get_oldpwd(t_list *env_list, t_list *cmd, int *finish_status)
{
	t_token	*cmd_content;
	int		cmd_index;
	char	*new_path;

	new_path = NULL;
	cmd_index = 0;
	cmd_content = (t_token *)cmd->next->content;
	if (ft_strncmp(cmd_content->token_content, "-", 2) == 0)
	{
		cmd_index = is_added_env("OLDPWD", env_list);
		if (cmd_index == -1)
		{
			printf("minishell: cd: OLDPWD not set\n");
			*finish_status = 1;
			return (NULL);
		}
		new_path = get_env_value(env_list, "OLDPWD", cmd_index);
	}
	return (new_path);
}

char	*get_homedir(t_list *env_list, int *finish_status)
{
	t_token	*cmd_content;
	int		cmd_index;
	char	*new_path;

	new_path = NULL;
	cmd_index = is_added_env("HOME", env_list);
	if (cmd_index == -1)
	{
		printf("minishell: cd: HOME not set\n");
		*finish_status = 1;
		return (NULL);
	}
	new_path = get_env_value(env_list, "HOME", cmd_index);
	return (new_path);
}

char	*get_env_value(t_list *env_list, char *value_name, int cmd_index)
{
	t_env	*env;
	char	*env_value;

	while (cmd_index > 0)
	{
		env_list = env_list->next;
		cmd_index--;
	}
	env = (t_env *)env_list->content;
	env_value = ft_strdup(env->value);
	return (env_value);
}
