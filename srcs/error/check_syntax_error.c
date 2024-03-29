/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:05:02 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/31 20:23:05 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

int	check_redirect_syntax_error(t_list *less_than, int *finish_status)
{
	t_token	*token;

	while (less_than != NULL)
	{
		token = (t_token *)less_than->content;
		if (token->status == RD_IN_ERROR || token->status == RD_OUT_ERROR
			|| token->token_content == NULL)
		{
			if (token->status == RD_IN_ERROR)
				printf("syntax error near unexpected token `<'\n");
			else if (token->status == RD_OUT_ERROR)
				printf("syntax error near unexpected token `>'\n");
			else if (token->token_content == NULL)
				printf("minishell: syntax error near unexpected token `[<>]'\n");
			*finish_status = 258;
			return (NG);
		}
		less_than = less_than->next;
	}
	return (OK);
}

int	check_pipe(t_list *tokens, t_parsed_token *parsed_token, int *finish_status)
{
	t_token	*last_token;
	t_list	*preproc_tokens;

	preproc_tokens = preprocess_tokens(tokens);
	last_token = (t_token *)ft_lstlast(preproc_tokens)->content;
	if (parsed_token->cmd == NULL && parsed_token->redirect == NULL)
	{
		printf("minishell : syntax error near unexpected token `|'\n");
		*finish_status = 258;
		ft_lstclear(&preproc_tokens, (void *)free_token);
		return (NG);
	}
	else if (last_token->status == TK_PIPE)
	{
		printf("minishell : syntax error close pipe `|'\n");
		*finish_status = 258;
		ft_lstclear(&preproc_tokens, (void *)free_token);
		return (NG);
	}
	ft_lstclear(&preproc_tokens, (void *)free_token);
	return (OK);
}

int	check_quote_syntax_error(t_list *token, int *finish_status)
{
	t_token	*content;

	while (token != NULL)
	{
		content = (t_token *)token->content;
		if (content->status == TK_ERROR)
		{
			printf("close quote!\n");
			*finish_status = 1;
			return (NG);
		}
		token = token->next;
	}
	return (OK);
}

int	check_syntax_error(t_list *list, t_list *token, int *finish_status)
{
	t_parsed_token	*parsed_token;

	while (list != NULL)
	{
		parsed_token = (t_parsed_token *)list->content;
		if (check_pipe(token, parsed_token, finish_status) == NG)
			return (NG);
		if (check_quote_syntax_error(token, finish_status) == NG)
			return (NG);
		if (check_redirect_syntax_error(parsed_token->redirect,
				finish_status) == NG)
			return (NG);
		list = list->next;
	}
	return (OK);
}
