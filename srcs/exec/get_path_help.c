/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:53:18 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/01 13:14:47 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

void	check_cmd_directory_current(char *cmd, int flag)
{
	struct stat	st;

	stat(cmd, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR && flag == CHILD && ft_strncmp(cmd, "./", 2) == 0)
	{
		printf("minishell: %s: is a directory\n", cmd);
		exit(126);
	}
}

bool	is_regular_file(char *path)
{
	struct stat	path_stat;

	if (ft_strchr(path, '/') != NULL)
		return (false);
	if (stat(path, &path_stat) == -1)
		return (true);
	if ((path_stat.st_mode & S_IFMT) == S_IFREG)
		return (true);
	return (false);
}
