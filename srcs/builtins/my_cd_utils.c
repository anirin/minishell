/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/18 17:19:27 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

// void	to_homedir(t_list *env_list)
// {
// 	if (getenv("HOME") != NULL)
// 	{
// 		overwrite_pwd(getenv("HOME"), env_list);
// 		chdir(getenv("HOME"));
// 	}
// 	else
// 		printf("HOME not set\n");
// }

// void	overwrite_pwd(char *new_path, t_list *env_list)
// {
// 	int	env_index;

// 	env_index = is_added_env("PWD", env_list);
// 	overwrite_env(env_index, new_path, env_list);
// }

// void	overwrite_oldpwd(t_list *env_list)
// {
// 	int		env_index;
// 	char	*crt_path;

// 	crt_path = getcwd(NULL, 0);
// 	env_index = is_added_env("OLDPWD", env_list);
// 	overwrite_env(env_index, crt_path, env_list);
// }
