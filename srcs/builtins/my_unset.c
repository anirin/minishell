/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:02:41 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/14 16:29:18 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	is_env_var(t_list *env_list, char *str_arg);
void	delete_env_var(t_list **env_list, char *str_arg);

void	my_unset(t_list **env_list, t_list *args)
{
	t_token	*str_arg;

	if (args == NULL)
		return ;
	else
	{
		str_arg = (t_token *)args->content;
		if (is_env_var(*env_list, str_arg->token_content) == true)
		{
			delete_env_var(env_list, str_arg->token_content);
		}
		else
			return ;
	}
}

bool	is_env_var(t_list *env_list, char *str_arg)
{
	t_env	*env;

	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (ft_strncmp(env->name, str_arg, ft_strlen(env->name)) == 0)
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

void	delete_env_var(t_list **env_list, char *str_arg)
{
	t_env	*env;
	void	*tmp;
	void	*start_prt;

	if ((*env_list) == NULL)
		return ;
	env = (t_env *)(*env_list)->content;
	start_prt = *env_list;
	if (ft_strncmp(env->name, str_arg, ft_strlen(env->name) + 1) == 0)
	{
		tmp = *env_list;
		(*env_list) = (*env_list)->next;
		free(tmp);
		return ;
	}
	while ((*env_list)->next != NULL)
	{
		env = (t_env *)(*env_list)->next->content;
		if (ft_strncmp(env->name, str_arg, ft_strlen(env->name) + 1) == 0)
		{
			tmp = (*env_list)->next;
			(*env_list)->next = (*env_list)->next->next;
			free(tmp);
			*env_list = start_prt;
			return ;
		}
		(*env_list) = (*env_list)->next;
	}
}
