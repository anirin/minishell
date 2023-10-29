/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:31:09 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 09:33:51 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parser.h"

char	*get_content(t_list *tokens)
{
	t_token	*token;
	char	*ret;

	if (tokens == NULL)
		return (NULL);
	token = (t_token *)tokens->content;
	if (token->status != TK_NORMAL && token->status != TK_DOLL)
		ret = NULL;
	else
	{
		token->status = TK_USED;
		ret = ft_strdup(token->token_content);
	}
	return (ret);
}

void	move_tokens_and_change_status_used(t_list **tokens)
{
	t_token	*token;

	token = (t_token *)(*tokens)->content;
	token->status = TK_USED;
	*tokens = (*tokens)->next;
	if (*tokens == NULL)
		return ;
	else
	{
		token = (t_token *)(*tokens)->content;
		if (token->status == TK_NORMAL)
		{
			token->status = TK_USED;
			*tokens = (*tokens)->next;
		}
	}
}

void	move_head(t_list **head)
{
	t_token	*token;

	while (1)
	{
		if (*head == NULL)
			break ;
		token = (t_token *)(*head)->content;
		if (token->status == TK_PIPE)
		{
			*head = (*head)->next;
			break ;
		}
		*head = (*head)->next;
	}
}
