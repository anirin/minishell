/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_to_string_parse_token.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:07:31 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/31 20:22:48 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

static char	**handle_append_case(char **parsed_env, char *token, int count)
{
	char	*tmp;

	parsed_env[0] = ft_substr(token, 0, count);
	parsed_env[1] = ft_strdup("+=");
	if (token[count + 2] != '\0')
	{
		tmp = ft_strdup(&token[count + 2]);
		parsed_env[2] = ft_strtrim(tmp, "\"");
		free(tmp);
	}
	else
		parsed_env[2] = ft_strdup("");
	return (parsed_env);
}

static char	**handle_assignment_case(char **parsed_env, char *token, int count)
{
	parsed_env[0] = ft_substr(token, 0, count);
	parsed_env[1] = ft_strdup("=");
	if (token[count + 1] != '\0')
		parsed_env[2] = ft_strdup(&token[count + 1]);
	else
		parsed_env[2] = ft_strdup("");
	return (parsed_env);
}

char	**parse_env(char *token)
{
	char	**parsed_env;
	int		count;
	int		i;

	count = 0;
	i = 0;
	parsed_env = ft_calloc(4, sizeof(char *));
	parsed_env[3] = NULL;
	while (token[i] != '\0')
	{
		if (ft_strncmp(&token[i], "+=", 2) == 0 && count != 0)
			return (handle_append_case(parsed_env, token, count));
		else if (ft_strncmp(&token[i], "=", 1) == 0 && count != 0)
			return (handle_assignment_case(parsed_env, token, count));
		count++;
		i++;
	}
	parsed_env[0] = ft_strdup(token);
	parsed_env[1] = NULL;
	parsed_env[2] = NULL;
	return (parsed_env);
}

t_list	*envp_convert_to_envlist(char **envp)
{
	int		i;
	t_list	*env_list;
	t_env	*env;
	t_list	*new;
	char	**parsed_env;

	i = 0;
	env_list = NULL;
	while (envp[i] != NULL)
	{
		env = malloc(sizeof(t_env));
		parsed_env = parse_env(envp[i]);
		env->name = ft_strdup(parsed_env[0]);
		env->value = ft_strdup(parsed_env[2]);
		new = ft_lstnew(env);
		ft_lstadd_back(&env_list, new);
		free(parsed_env[0]);
		free(parsed_env[1]);
		free(parsed_env[2]);
		free(parsed_env);
		i++;
	}
	return (env_list);
}
