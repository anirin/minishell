/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:53:18 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/31 21:56:24 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

char	*is_regular_file(char *path, int flag)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode) && flag == CHILD && ft_strncmp(path, "./",
			2) != 0)
	{
		printf("minishell: %s: command not found\n", path);
		exit(127);
	}
	else
		return (strdup(path));
	return (NULL);
}
