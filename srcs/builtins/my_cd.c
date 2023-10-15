/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/14 21:31:24 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	is_accessible(char *new_path, char *input_path);
bool	is_directory(char *new_path, char *input_path);
char	*get_new_path(char *input_path);
char	*trim_last_segment(char *crt_path);

// cd [input_path]
void	my_cd(t_list *env_list, t_list *args)
{
	char	*input_path;
	char	*new_path;
	t_token	*content;

	overwrite_oldpwd(env_list);
	if (args == NULL)
	{
		to_homedir(env_list);
		return ;
	}
	content = (t_token *)args->content;
	input_path = content->token_content;
	new_path = get_new_path(input_path);
	if (is_directory(new_path, input_path) == false)
		return ;
	if (is_accessible(new_path, input_path) == false)
		return ;
	chdir(new_path);
	overwrite_pwd(new_path, env_list);
}

bool	is_accessible(char *new_path, char *input_path)
{
	if (access(input_path, X_OK) != 0)
	{
		printf("minishell: cd : %s:Permission denied\n", input_path);
		return (false);
	}
	else
		return (true);
}

bool	is_directory(char *new_path, char *input_path)
{
	struct stat	*stat_info;

	stat_info = (struct stat *)malloc(sizeof(struct stat) * 1);
	if (stat_info == NULL)
		exit(1);
	if (ft_strncmp(new_path, "", 1) == 0)
		return (true);
	if (stat(new_path, stat_info) != 0)
	{
		if (errno == ENOENT)
			printf("minishell: cd: %s: Not such file or directory\n",
				input_path);
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

char	*get_new_path(char *input_path)
{
	char	*crt_path;
	char	*new_path;
	char	**path_part;
	int		i;

	crt_path = getcwd(NULL, 0);
	path_part = ft_split(input_path, '/');
	if (*path_part == NULL)
	{
		new_path = input_path;
	}
	i = 0;
	while (path_part[i] != NULL)
	{
		if (ft_strncmp(path_part[i], "..", ft_strlen(path_part[i]) + 1) == 0)
			new_path = trim_last_segment(crt_path);
		else if (ft_strncmp(path_part[i], ".", 2) == 0)
			new_path = crt_path;
		else
		{
			new_path = ft_strjoin(crt_path, "/");
			new_path = ft_strjoin(new_path, path_part[i]);
		}
		crt_path = new_path;
		i++;
	}
	return (new_path);
}

/*
before : [/Users/hnakai/42curcus/Rank04/minishell]
after  : [/Users/hnakai/42curcus/Rank04]
*/
char	*trim_last_segment(char *crt_path)
{
	int		i;
	int		len;
	char	*new_path;

	i = 0;
	new_path = malloc(sizeof(char *) * (ft_strlen(crt_path) + 1));
	if (new_path == NULL)
		exit(1);
	if (ft_strncmp(crt_path, "/", 2) == 0)
	{
		ft_strlcpy(new_path, crt_path, i + 1);
		return (new_path);
	}
	len = ft_strlen(crt_path);
	i = len - 1;
	if (crt_path[i] == '/')
		i--;
	while (crt_path[i] != '\0')
	{
		if (crt_path[i] == '/')
			break ;
		i--;
	}
	ft_strlcpy(new_path, crt_path, i + 1);
	return (new_path);
}
