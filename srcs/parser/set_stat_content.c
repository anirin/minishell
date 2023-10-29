/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stat_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:21:52 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 09:34:05 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parser.h"

static int	check_token_status(t_token *token)
{
	if (token->status == TK_NORMAL || token->status == TK_DOUBLE_QUOTE
		|| token->status == TK_SINGLE_QUOTE)
		return (1);
	return (0);
}

char	*get_new_content(t_list **tokens)
{
	char	*new_content;
	char	*tmp;
	t_token	*token;

	token = (t_token *)(*tokens)->content;
	if (!check_token_status(token))
	{
		new_content = ft_strdup(token->token_content);
		*tokens = (*tokens)->next;
	}
	else
	{
		new_content = ft_strdup("");
		while ((*tokens) != NULL && token != NULL && check_token_status(token))
		{
			tmp = new_content;
			new_content = ft_strjoin(tmp, token->token_content);
			free(tmp);
			*tokens = (*tokens)->next;
			if (*tokens != NULL)
				token = (t_token *)(*tokens)->content;
		}
	}
	return (new_content);
}

int	get_new_status(t_list *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	if (token->status != TK_DOUBLE_QUOTE && token->status != TK_SINGLE_QUOTE)
		return (token->status);
	else
		return (TK_NORMAL);
}
