/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_isspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:27:41 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 21:39:07 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_env.h"
#include "libft.h"
#include "main.h"

static void	add_token_to_list(t_list **list, char *content, int status)
{
	t_token	*token;
	t_list	*new;

	token = malloc(sizeof(t_token));
	token->token_content = content;
	token->status = status;
	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
}

static void	handle_spaces(char *str, int *i, t_list **splited_env)
{
	int	count;

	count = 0;
	while (str[*i] != '\0' && ft_isspace(str[*i]) == UT_SPACE)
	{
		count++;
		(*i)++;
	}
	if (count > 0)
		add_token_to_list(splited_env, ft_strdup(" "), TK_SPACE);
}

static void	handle_not_spaces(char *str, int *i, t_list **splited_env)
{
	int	count;

	count = 0;
	while (str[*i] != '\0' && ft_isspace(str[*i]) == UT_NOT_SPACE)
	{
		count++;
		(*i)++;
	}
	if (count > 0)
		add_token_to_list(splited_env, ft_substr(str, *i - count, count),
			TK_NORMAL);
}

t_list	*split_by_isspace(char *str)
{
	t_list	*splited_env;
	int		i;

	i = 0;
	splited_env = NULL;
	while (str[i])
	{
		if (str[i] == '\0')
		{
			add_token_to_list(&splited_env, ft_strdup(" "), TK_ENV_SPACE);
			break ;
		}
		handle_spaces(str, &i, &splited_env);
		handle_not_spaces(str, &i, &splited_env);
	}
	return (splited_env);
}
