/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:27:23 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/04 17:08:01 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_env.h"
#include "libft.h"
#include "main.h"

char	*find_env_name(char *doller_token, t_list *env_list,
		int *finish_status)
{
	t_env	*env;

	if (ft_strlen(doller_token) == 1)
		return (ft_strdup("$"));
	else if (ft_strncmp(doller_token, "$$", 2) == 0)
		return (ft_strdup("[PID]"));
	if (ft_strncmp(&doller_token[1], "?", 2) == 0)
		return (ft_itoa(*finish_status));
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (env->value != NULL && ft_strncmp(&doller_token[1], env->name,
				ft_strlen(env->name) + 1) == 0)
		{
			return (ft_strdup(env->value));
		}
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}

char	*parsed_tokens_to_str(t_list *parsed_tokens)
{
	char	*ret;
	char	*tmp;

	ret = ft_strdup("");
	while (parsed_tokens != NULL)
	{
		tmp = ret;
		ret = ft_strjoin(tmp, parsed_tokens->content);
		free(tmp);
		parsed_tokens = parsed_tokens->next;
	}
	return (ret);
}

bool	is_heardoc(t_list *prev)
{
	t_token	*token;

	if (prev == NULL)
		return (false);
	token = (t_token *)prev->content;
	if (ft_strncmp(token->token_content, "<<", 3) == 0)
		return (true);
	return (false);
}
