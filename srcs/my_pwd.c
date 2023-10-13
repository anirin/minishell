/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:09:10 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/06 23:20:14 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	my_pwd(void)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * PATH_SIZE);
	if (path == NULL)
		exit(1);
	printf("%s\n", getcwd(path, PATH_SIZE));
	free(path);
}
