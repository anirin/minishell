/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/07 14:23:25 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	my_cd(char *str)
{
	char *path;

	path = (char *)malloc(sizeof(char) * PATH_SIZE);
	if (path == NULL)
		exit(1);
	path = getcwd(path, PATH_SIZE);
	if (ft_strncmp(str, "..", 2) == 0)
		chdir();
	else if (ft_strncmp(str, ".", 1) == 0)
		chdir();
	else if (str != NULL)
		chdir();
	else if ()
		chdir();
}

//test