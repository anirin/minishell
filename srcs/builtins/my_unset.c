/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:02:41 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/29 21:15:39 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	is_env_var(t_list *env_list, char *str_arg);
void	delete_env_var(t_list **env_list, char *str_arg);
void	delete_first_env(t_list **data, t_env *env);
void	delete_after_first_env(t_list *env_list, t_env *env);

void	my_unset(t_list **env_list, t_list *args)
{
	t_token	*str_arg;

	if (args == NULL)
	{
		return ;
	}
	else
	{
		while (args != NULL)
		{
			str_arg = (t_token *)args->content;
			if (is_env_var(*env_list, str_arg->token_content) == true)
			{
				delete_env_var(env_list, str_arg->token_content);
			}
			args = args->next;
		}
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

void	delete_env_var(t_list **data, char *str_arg)
{
	t_env	*env;
	t_list	*env_list;

	env_list = *data;
	if (env_list == NULL)
		return ;
	env = (t_env *)env_list->content;
	if (ft_strncmp(env->name, str_arg, ft_strlen(env->name) + 1) == 0)
	{
		delete_first_env(data, env);
		return ;
	}
	while (env_list->next != NULL)
	{
		env = (t_env *)env_list->next->content;
		if (ft_strncmp(env->name, str_arg, ft_strlen(env->name) + 1) == 0)
		{
			delete_after_first_env(env_list, env);
			return ;
		}
		env_list = env_list->next;
	}
}

void	delete_first_env(t_list **data, t_env *env)
{
	t_list	*tmp;

	tmp = *data;
	*data = (*data)->next;
	free_env(env);
	free(tmp);
}

void	delete_after_first_env(t_list *env_list, t_env *env)
{
	t_list	*tmp;

	tmp = env_list->next;
	env_list->next = env_list->next->next;
	free_env(env);
	free(tmp);
}
