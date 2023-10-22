/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:09:10 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/22 20:26:59 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		printf("%s\n", getcwd(NULL, 0));
}
