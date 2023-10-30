/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:07:34 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/30 17:31:06 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

int	is_added_env(char *env_name, t_list *env_list)
{
	int		count;
	t_env	*env;

	count = 0;
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (ft_strncmp(env->name, env_name, ft_strlen(env->name) + 1) == 0)
			return (count);
		env_list = env_list->next;
		count++;
	}
	return (-1);
}

static void	print_export(void *env_list)
{
	t_env	*env;

	env = (t_env *)env_list;
	printf("declare -x %s=\"%s\"\n", env->name, env->value);
}

void	update_env_end(char *path, t_list **env_list)
{
	int	env_index;

	env_index = is_added_env("_", *env_list);
	overwrite_env(env_index, path, *env_list);
}

static void	handle_args(t_list *args, t_list **env_list, int *finish_status)
{
	int		env_index;
	char	**parsed_env;

	while (args != NULL)
	{
		parsed_env = parse_env(((t_token *)args->content)->token_content);
		if (!check_export_error(parsed_env[0], finish_status))
		{
			free_array(parsed_env);
			break ;
		}
		env_index = is_added_env(parsed_env[0], *env_list);
		if (env_index != -1)
		{
			if (parsed_env[1] && !ft_strncmp(parsed_env[1], "+=", 3))
				append_env(env_index, parsed_env[2], *env_list);
			else if (parsed_env[1] && !ft_strncmp(parsed_env[1], "=", 2))
				overwrite_env(env_index, parsed_env[2], *env_list);
		}
		else
			add_env(parsed_env, env_list, finish_status);
		free_array(parsed_env);
		args = args->next;
	}
}

void	my_export(t_list **env_list, t_list *args, int *finish_status)
{
	if (!args)
	{
		ft_lstiter(*env_list, (void *)print_export);
		return ;
	}
	handle_args(args, env_list, finish_status);
}
