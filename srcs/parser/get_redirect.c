/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:04:58 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 09:31:04 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parser.h"

static int	get_greater_than_status(char *str)
{
	if (ft_strlen(str) == 1)
		return (RD_OUT);
	else if (ft_strlen(str) == 2)
		return (RD_APPEND);
	else
		return (RD_OUT_ERROR);
}

static int	get_less_than_status(char *str)
{
	if (ft_strlen(str) == 1)
		return (RD_IN);
	else if (ft_strlen(str) == 2)
		return (RD_HEAEDOC);
	else
		return (RD_IN_ERROR);
}

static void	handle_redirect(t_list **tokens, t_list **r_tokens, int status)
{
	t_token	*token;
	t_token	*new;

	token = (t_token *)(*tokens)->content;
	new = malloc(sizeof(t_token));
	if (status == TK_LESS_THAN)
		new->status = get_less_than_status(token->token_content);
	else if (status == TK_GREATER_THAN)
		new->status = get_greater_than_status(token->token_content);
	new->token_content = get_content((*tokens)->next);
	ft_lstadd_back(r_tokens, ft_lstnew(new));
	move_tokens_and_change_status_used(tokens);
}

t_list	*get_redirect_tokens(t_list *tokens)
{
	t_list	*redirect_tokens;
	t_token	*token;

	redirect_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == TK_LESS_THAN || token->status == TK_GREATER_THAN)
			handle_redirect(&tokens, &redirect_tokens, token->status);
		else if (token->status == TK_PIPE)
			break ;
		else
			tokens = tokens->next;
	}
	return (redirect_tokens);
}
