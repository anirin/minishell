/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_doller_and_parse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:27:34 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 21:35:07 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_env.h"
#include "libft.h"
#include "main.h"

static void	add_token_without_dollar(char *token, int *i,
		t_list **parsed_tokens)
{
	int		count;
	char	*str;

	count = 0;
	while (token[*i] != '\0' && token[*i] != '$')
	{
		count++;
		(*i)++;
	}
	if (count > 0)
	{
		str = ft_substr(token, *i - count, count);
		ft_lstadd_back(parsed_tokens, ft_lstnew(str));
	}
}

static void	add_token_with_dollar(char *token, int *i, t_list **parsed_tokens)
{
	int		count;
	char	*str;

	if (token[*i] != '$')
		return ;
	i++;
	count = 1;
	while (token[*i] != '\0' && ft_isspace(token[*i]) == UT_NOT_SPACE
		&& token[*i] != '\'' && token[*i] != '\"')
	{
		count++;
		(*i)++;
	}
	if (count > 0)
	{
		str = ft_substr(token, *i - count, count);
		ft_lstadd_back(parsed_tokens, ft_lstnew(str));
	}
}

t_list	*find_dollar_and_parse(char *token)
{
	t_list	*parsed_tokens;
	int		i;

	i = 0;
	parsed_tokens = NULL;
	while (token[i] != '\0')
	{
		add_token_without_dollar(token, &i, &parsed_tokens);
		add_token_with_dollar(token, &i, &parsed_tokens);
	}
	return (parsed_tokens);
}
