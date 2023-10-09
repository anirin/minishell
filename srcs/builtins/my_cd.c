/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/09 23:02:45 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

// cd [input_path]
void	my_cd(t_list *args)
{
	char	*input_path;
	char	*new_path;
	t_token	*content;

	content = (t_token *)args->content;
	input_path = content->token_content;
	new_path = get_new_path(input_path);
	if (is_directory(new_path) == false)
		return ;
	if (is_accessible(new_path) == false)
		return ;
	chdir(new_path);
}

bool	is_accessible(char *new_path)
{
	if (access(new_path, X_OK) != 0)
	{
		printf("cd : %s:Permission denied\n", new_path);
		return (false);
	}
	else
		return (true);
}

bool	is_directory(char *new_path)
{
	struct stat	*stat_info;

	if (stat(new_path, stat_info) != 0)
	{
		printf("cd: %s:no such file or directory\n", new_path);
		return (false);
	}
	else
		return (true);
}

char	*get_new_path(char *input_path)
{
	char	*crt_path;
	char	*new_path;
	char	**path_part;
	int		i;

	crt_path = getcwd(NULL, 0);
	path_part = ft_split(input_path, '/');
	i = 0;
	while (path_part[i] != NULL)
	{
		if (ft_strncmp(path_part[i], "..", ft_strlen(path_part[i])) == 0)
			new_path = trim_last_segment(crt_path);
		else if (ft_strncmp(path_part[i], ".", 1) == 0)
			new_path = crt_path;
		else
		{
			new_path = ft_strjoin(new_path, path_part[i]);
			new_path = ft_strjoin(new_path, "/");
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

	new_path = malloc(sizeof(char *) * (ft_strlen(crt_path) + 1));
	if (new_path == NULL)
		exit(1);
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
