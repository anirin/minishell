#include "libft.h"
#include "main.h"

int	check_redirect_syntax_error(t_list *less_than, t_list *shell_list)
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
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		else if (token->status == RD_OUT_ERROR)
		{
			printf("syntax error near unexpected token `");
			printf(">"); //ここは面倒だ
			printf("'\n");
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		else if (token->token_content == NULL)
		{
			printf("minishell: syntax error near unexpected token `[redirect]'\n");
			// < > にする
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		less_than = less_than->next;
	}
	return (OK);
}

int		check_last_pipe(t_list *tokens, t_list *shell_list)
{
	t_token *last_token;
	t_list *preproc_tokens;

	preproc_tokens = preprocess_tokens(tokens);
	last_token = (t_token *)ft_lstlast(preproc_tokens)->content;
	if (last_token->status == TK_PIPE)
	{
		printf("minishell : syntax error close pipe `|'\n");
		modify_finish_status(shell_list, 258);
		ft_lstclear(&preproc_tokens, (void *)free_token);
		return (NG);
	}
	ft_lstclear(&preproc_tokens, (void *)free_token);
	return (OK);
}

int		check_quote_syntax_error(t_list *token, t_list *shell_list)
{
	t_token *content;
	
	while (token != NULL)
	{
		content = (t_token *)token->content;
		if (content->status == TK_ERROR)
		{
			printf("quote wo to ji ro\n");
			modify_finish_status(shell_list, 1);
			return (NG);
		}
		token = token->next;
	}
	return (OK);
}

int		check_syntax_error(t_list *list, t_list *token, t_list *shell_list)
{
	int		flag;
	t_parsed_token *parsed_token;
	
	flag = OK;
	while (list != NULL)
	{
		if (check_last_pipe(token, shell_list) == NG)
			return (NG);
		parsed_token = (t_parsed_token *)list->content;
		if (check_quote_syntax_error(token, shell_list) == NG)
			return (NG);
		if (check_redirect_syntax_error(parsed_token->redirect, shell_list) == NG)
			return (NG);
		list = list->next;
	}
	return (OK);
}