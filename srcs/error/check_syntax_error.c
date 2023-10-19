#include "libft.h"
#include "main.h"

int	check_redirect_syntax_error(t_list *redirect, t_list *shell_list)
{
	t_token *token;

	while (redirect != NULL)
	{
		token = (t_token *)redirect->content;
		if (token->status == RD_ERROR)
		{
			printf("minishell: syntax error near unexpected token `redirect'\n");
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		if (token->token_content == NULL)
		{
			printf("minishell: syntax error near unexpected token `redirect'\n");
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		redirect = redirect->next;
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
		// if (parsed_token->cmd == NULL)
		// {
		// 	printf("minishell: syntax error near unexpected token `|'\n");
		// 	modify_finish_status(shell_list, 258);
		// 	return (NG);
		// }ここなんとかせにゃならん
		if (check_redirect_syntax_error(parsed_token->redirect, shell_list) == NG)
			return (NG);
		list = list->next;
	}
	return (OK);
}