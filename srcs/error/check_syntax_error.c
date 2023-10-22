#include "libft.h"
#include "main.h"

int	check_redirect_syntax_error(t_list *less_than)
{
	t_token *token;

	while (less_than != NULL)
	{
		token = (t_token *)less_than->content;
		if (token->status == RD_IN_ERROR)
		{
			printf("syntax error near unexpected token `");
			printf("<"); //ここは面倒だ
			printf("'\n");
			g_finish_status = 258;
			return (NG);
		}
		else if (token->status == RD_OUT_ERROR)
		{
			printf("syntax error near unexpected token `");
			printf(">"); //ここは面倒だ
			printf("'\n");
			g_finish_status = 258;
			return (NG);
		}
		else if (token->token_content == NULL)
		{
			printf("minishell: syntax error near unexpected token `[redirect]'\n");
			// < > にする
			g_finish_status = 258;
			return (NG);
		}
		less_than = less_than->next;
	}
	return (OK);
}

int		check_pipe(t_list *tokens, t_parsed_token *parsed_token)
{
	t_token *last_token;
	t_list *preproc_tokens;

	preproc_tokens = preprocess_tokens(tokens);
	last_token = (t_token *)ft_lstlast(preproc_tokens)->content;
	if (parsed_token->cmd == NULL && parsed_token->redirect == NULL)
	{
		printf("minishell : syntax error near unexpected token `|'\n");
		g_finish_status = 258;
		ft_lstclear(&preproc_tokens, (void *)free_token);
		return (NG);
	}
	else if (last_token->status == TK_PIPE)
	{
		printf("minishell : syntax error close pipe `|'\n");
		g_finish_status = 258;
		ft_lstclear(&preproc_tokens, (void *)free_token);
		return (NG);
	}
	ft_lstclear(&preproc_tokens, (void *)free_token);
	return (OK);
}

int		check_quote_syntax_error(t_list *token)
{
	t_token *content;
	
	while (token != NULL)
	{
		content = (t_token *)token->content;
		if (content->status == TK_ERROR)
		{
			printf("quote wo to ji ro\n");
			g_finish_status = 1;
			return (NG);
		}
		token = token->next;
	}
	return (OK);
}

int		check_syntax_error(t_list *list, t_list *token)
{
	int		flag;
	t_parsed_token *parsed_token;
	
	flag = OK;
	while (list != NULL)
	{
		parsed_token = (t_parsed_token *)list->content;
		if (check_pipe(token, parsed_token) == NG)
			return (NG);
		if (check_quote_syntax_error(token) == NG)
			return (NG);
		if (check_redirect_syntax_error(parsed_token->redirect) == NG)
			return (NG);
		list = list->next;
	}
	return (OK);
}