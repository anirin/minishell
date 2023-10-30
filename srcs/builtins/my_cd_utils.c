/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:00:13 by hnakai            #+#    #+#             */
/*   Updated: 2023/10/30 17:37:31 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	is_directory(char *input_path, int *finish_status);
bool	is_accessible(char *input_path, int *finish_status);

int	overwrite_pwd(t_list *env_list)
{
	int		env_index;
	char	*crt_path;

	crt_path = getcwd(NULL, 0);
	if (crt_path == NULL)
	{
		ft_putstr_fd("error retrieving current directory:getcwd: "
			"cannot access parent directories\n",
			STDERR_FILENO);
		return (FAIL);
	}
	env_index = is_added_env("PWD", env_list);
	if (env_index == -1)
	{
		free(crt_path);
		return (SUCCESS);
	}
	overwrite_env(env_index, crt_path, env_list);
	free(crt_path);
	return (SUCCESS);
}

int	overwrite_oldpwd(t_list *env_list)
{
	int		env_index;
	char	*crt_path;

	crt_path = getcwd(NULL, 0);
	if (crt_path == NULL)
	{
		ft_putstr_fd("error retrieving current directory: "
			"getcwd: cannot access parent directories\n",
			STDERR_FILENO);
		return (FAIL);
	}
	env_index = is_added_env("OLDPWD", env_list);
	if (env_index == -1)
	{
		free(crt_path);
		return (SUCCESS);
	}
	overwrite_env(env_index, crt_path, env_list);
	free(crt_path);
	return (SUCCESS);
}

char	*get_env_value(t_list *env_list, char *value_name, int cmd_index)
{
	t_env	*env;
	char	*env_value;

	(void)value_name;
	while (cmd_index > 0)
	{
		env_list = env_list->next;
		cmd_index--;
	}
	env = (t_env *)env_list->content;
	env_value = ft_strdup(env->value);
	return (env_value);
}

bool	is_cd_error(char *new_path, int *finish_status)
{
	if (is_accessible(new_path, finish_status) == false)
		return (false);
	if (is_directory(new_path, finish_status) == false)
		return (false);
	return (true);
}
