/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:21:50 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 09:38:30 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parser.h"

static void	trim_quote(void *content)
{
	char	*tmp;
	t_token	*token;

	token = (t_token *)content;
	tmp = token->token_content;
	if (token->status == TK_SINGLE_QUOTE)
	{
		token->token_content = ft_strtrim((const char *)tmp, "\'");
		token->status = TK_SINGLE_QUOTE;
		free(tmp);
	}
	else if (token->status == TK_DOUBLE_QUOTE)
	{
		token->token_content = ft_strtrim((const char *)tmp, "\"");
		token->status = TK_DOUBLE_QUOTE;
		free(tmp);
	}
}

t_list	*preprocess_tokens(t_list *tokens)
{
	t_list	*prepro_tokens;
	t_list	*new;
	t_token	*token;
	t_token	*new_token;

	prepro_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status != TK_SPACE)
		{
			new_token = (t_token *)malloc(sizeof(t_token));
			new_token->status = get_new_status(tokens);
			new_token->token_content = get_new_content(&tokens);
			new = ft_lstnew(new_token);
			ft_lstadd_back(&prepro_tokens, new);
		}
		else if (token->status == TK_SPACE)
			tokens = tokens->next;
	}
	return (prepro_tokens);
}

static t_list	*get_list(t_list *tokens)
{
	t_list			*parsed_list;
	t_list			*new;
	t_parsed_token	*parsed_token;
	t_list			*head;

	head = tokens;
	parsed_list = NULL;
	while (head != NULL)
	{
		parsed_token = malloc(sizeof(t_parsed_token));
		parsed_token->redirect = get_redirect_tokens(head);
		parsed_token->cmd = get_cmd_tokens(head);
		parsed_token->args = get_args_tokens(head);
		new = ft_lstnew(parsed_token);
		ft_lstadd_back(&parsed_list, new);
		move_head(&head);
	}
	return (parsed_list);
}

t_list	*parser(t_list **tokens, t_list *env_list, int *finish_status)
{
	t_list	*preproc_tokens;
	t_list	*ret_tokens;

	ft_lstiter(*tokens, trim_quote);
	expand_env(tokens, env_list, finish_status);
	preproc_tokens = preprocess_tokens(*tokens);
	ret_tokens = get_list(preproc_tokens);
	ft_lstclear(&preproc_tokens, (void *)free_token);
	return (ret_tokens);
}
