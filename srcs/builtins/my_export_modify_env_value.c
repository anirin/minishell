/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_modify_env_value.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:07:39 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 10:11:43 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

void	append_env(int env_index, char *env_content, t_list *env_list)
{
	char	*tmp;
	t_env	*env;

	while (env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	env = (t_env *)env_list->content;
	tmp = env->value;
	env->value = ft_strjoin(tmp, env_content);
	free(tmp);
}

void	overwrite_env(int env_index, char *env_value, t_list *env_list)
{
	t_env	*env;

	while (env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	env = (t_env *)env_list->content;
	free(env->value);
	env->value = ft_strdup(env_value);
}

void	add_env(char **parsed_env, t_list **env_list, int *finish_status)
{
	char	*new_env_value;
	t_list	*new_lst;
	t_env	*new_env;

	if (ft_strncmp(parsed_env[0], "=", 1) == 0)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(parsed_env[0], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		*finish_status = 1;
		return ;
	}
	new_env = malloc(sizeof(t_env));
	if (parsed_env[1] != NULL)
		new_env_value = ft_strdup(parsed_env[2]);
	else
		new_env_value = NULL;
	new_env->name = ft_strdup(parsed_env[0]);
	new_env->value = new_env_value;
	new_lst = ft_lstnew(new_env);
	ft_lstadd_back(env_list, new_lst);
}
