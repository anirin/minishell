/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:06:25 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 09:33:07 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parser.h"

static void	add_new_token(t_list **cmd_tokens, t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->token_content = ft_strdup(token->token_content);
	new->status = TK_NORMAL;
	ft_lstadd_back(cmd_tokens, ft_lstnew(new));
	token->status = TK_USED;
}

t_list	*get_cmd_tokens(t_list *tokens)
{
	t_list	*cmd_tokens;
	t_token	*token;
	int		count;

	cmd_tokens = NULL;
	count = 0;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == TK_PIPE)
			break ;
		if (token->status != TK_USED
			&& (count == 0 || (count >= 1 && token->token_content[0] == '-')))
		{
			add_new_token(&cmd_tokens, token);
			count++;
		}
		else
			break ;
		tokens = tokens->next;
	}
	return (cmd_tokens);
}

t_list	*get_args_tokens(t_list *tokens)
{
	t_list	*args_tokens;
	t_token	*token;
	t_token	*new;

	args_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == TK_PIPE)
		{
			break ;
		}
		else if (token->status != TK_USED)
		{
			new = malloc(sizeof(t_token));
			new->token_content = ft_strdup(token->token_content);
			new->status = TK_NORMAL;
			ft_lstadd_back(&args_tokens, ft_lstnew(new));
			token->status = TK_USED;
		}
		tokens = tokens->next;
	}
	return (args_tokens);
}
