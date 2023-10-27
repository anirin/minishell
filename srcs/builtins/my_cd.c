/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/27 17:07:11 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	is_cd_error(char *new_path, int *finish_status);
bool	is_accessible(char *input_path, int *finish_status);
bool	is_directory(char *input_path, int *finish_status);
char	*get_homedir(t_list *env_list, int *finish_status);
char	*get_oldpwd(t_list *env_list, t_list *cmd, int *finish_status);
int		overwrite_oldpwd(t_list *env_list);
int		overwrite_pwd(t_list *env_list);
char	*get_env_value(t_list *env_list, char *value_name, int cmd_index);

void	my_cd(t_list *env_list, t_list *cmd, t_list *args, int *finish_status)
{
	char	*new_path;
	t_token	*args_content;

	if (args == NULL)
	{
		if (cmd != NULL && cmd->next != NULL)
			new_path = get_oldpwd(env_list, cmd, finish_status);
		else
			new_path = get_homedir(env_list, finish_status);
	}
	else
	{
		args_content = (t_token *)args->content;
		new_path = ft_strdup(args_content->token_content);
	}
	if (new_path == NULL || ft_strncmp(new_path, "", 1) == 0)
		return (free(new_path));
	if (is_cd_error(new_path, finish_status) == false)
		return (free(new_path));
	if (overwrite_oldpwd(env_list) != SUCCESS)
		return (free(new_path));
	chdir(new_path);
	free(new_path);
	if (overwrite_pwd(env_list) != SUCCESS)
		return ;
}

bool	is_accessible(char *input_path, int *finish_status)
{
	if (access(input_path, X_OK) != 0)
	{
		print_err("cd");
		*finish_status = 1;
		return (false);
	}
	else
		return (true);
}

bool	is_directory(char *input_path, int *finish_status)
{
	struct stat	*stat_info;

	stat_info = (struct stat *)malloc(sizeof(struct stat) * 1);
	if (stat_info == NULL)
		exit(1);
	if (stat(input_path, stat_info) != 0)
	{
		if (errno == ENOENT)
			print_err("cd");
		*finish_status = 1;
		free((void *)stat_info);
		return (false);
	}
	if ((stat_info->st_mode & S_IFMT) != S_IFDIR)
	{
		print_err("cd");
		*finish_status = 1;
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
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
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
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		*finish_status = 1;
		return (NULL);
	}
	new_path = get_env_value(env_list, "HOME", cmd_index);
	return (new_path);
}
