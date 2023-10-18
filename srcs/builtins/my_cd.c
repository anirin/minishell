/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/18 23:14:31 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	is_accessible(char *input_path);
bool	is_directory(char *input_path);
char	*get_env_value(t_list *env_list, char *value_name, int cmd_index);
char	*get_oldpwd(t_list *env_list, t_list *cmd);
char	*get_homedir(t_list *env_list);

void	my_cd(t_list *env_list, t_list *cmd, t_list *args)
{
	char	*new_path;
	t_token	*args_content;

	if (args == NULL)
	{
		if (cmd != NULL && cmd->next != NULL)
			new_path = get_oldpwd(env_list, cmd);
		else
			new_path = get_homedir(env_list);
	}
	else
	{
		overwrite_oldpwd(env_list);
		args_content = (t_token *)args->content;
		new_path = args_content->token_content;
	}
	if (new_path == NULL)
		return ;
	if (is_directory(new_path) == false)
		return ;
	if (is_accessible(new_path) == false)
		return ;
	chdir(new_path);
	overwrite_pwd(env_list);
	return ;
}

void	overwrite_pwd(t_list *env_list)
{
	int		env_index;
	char	*crt_path;

	crt_path = getcwd(NULL, 0);
	env_index = is_added_env("PWD", env_list);
	if (env_index == -1)
		return ;
	overwrite_env(env_index, crt_path, env_list);
}

void	overwrite_oldpwd(t_list *env_list)
{
	int		env_index;
	char	*crt_path;

	crt_path = getcwd(NULL, 0);
	env_index = is_added_env("OLDPWD", env_list);
	if (env_index == -1)
		return ;
	overwrite_env(env_index, crt_path, env_list);
}

bool	is_accessible(char *input_path)
{
	if (access(input_path, X_OK) != 0)
	{
		printf("minishell: cd : %s:Permission denied\n", input_path);
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
	// if (ft_strncmp(new_path, "", 1) == 0)
	// 	return (true);
	if (stat(input_path, stat_info) != 0)
	{
		if (errno == ENOENT)
		{
			printf("minishell : cd");
			// fprintf(stderr, "エラーが発生しました");
			// fflush(stdout);
			perror(input_path);
		}
		free((void *)stat_info);
		return (false);
	}
	if ((stat_info->st_mode & S_IFMT) != S_IFDIR)
	{
		printf("minishell: cd: %s: Not a directory\n", input_path);
		free((void *)stat_info);
		return (false);
	}
	else
	{
		free((void *)stat_info);
		return (true);
	}
}

char	*get_oldpwd(t_list *env_list, t_list *cmd)
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
			perror("minishell: cd: OLDPWD not set");
			return (NULL);
		}
		new_path = get_env_value(env_list, "OLDPWD", cmd_index);
	}
	return (new_path);
}

char	*get_homedir(t_list *env_list)
{
	t_token	*cmd_content;
	int		cmd_index;
	char	*new_path;

	new_path = NULL;
	cmd_index = is_added_env("HOME", env_list);
	if (cmd_index == -1)
	{
		perror("minishell: cd: HOME not set");
		return (NULL);
	}
	new_path = get_env_value(env_list, "HOME", cmd_index);
	return (new_path);
}

char	*get_env_value(t_list *env_list, char *value_name, int cmd_index)
{
	t_env *env;

	while (cmd_index > 0)
	{
		env_list = env_list->next;
		cmd_index--;
	}
	env = (t_env *)env_list->content;
	return (env->value);
}
