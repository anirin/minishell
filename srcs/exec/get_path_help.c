/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:53:18 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/31 22:47:44 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

void	check_cmd_directory_current(char *cmd, int flag)
{
	struct stat	st;

	stat(cmd, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR && flag == CHILD && ft_strncmp(cmd,
			"./", 2) == 0)
	{
		printf("minishell: %s: is a directory\n", cmd);
		exit(126);
	}
}

char	*is_regular_file(char *path, int flag)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1 && flag == CHILD)
	{
		printf("minishell: %s: command not found\n", path);
		exit(127);
	}
	if ((path_stat.st_mode & S_IFMT) == S_IFREG && flag == CHILD
		&& ft_strncmp(path, "./", 2) != 0)
	{
		printf("minishell: %s: command not found\n", path);
		exit(127);
	}
	else
		return (ft_strdup(path));
	return (NULL);
}
