#include "libft.h"
#include "main.h"

static void	modify_finish_status(t_list *shell_list, int status)
{
	t_env	*shell;

	shell = (t_env *)shell_list->content;
	free(shell->value);
	shell->value = ft_itoa(status);
}

static int	check_greater_than_syntax_error(t_list *greater_than, t_list *shell_list)
{
	t_token *token;

	while (greater_than != NULL)
	{
		token = (t_token *)greater_than->content;
		if (token->status == RD_ERROR)
		{
			printf("syntax error near unexpected token `");
			printf(">"); //ここは面倒だ
			printf("'\n");
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		if (token->token_content == NULL)
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		greater_than = greater_than->next;
	}
	return (OK);
}

int	check_less_than_syntax_error(t_list *less_than, t_list *shell_list)
{
	t_token *token;

	while (less_than != NULL)
	{
		token = (t_token *)less_than->content;
		if (token->status == RD_ERROR)
		{
			printf("syntax error near unexpected token `");
			printf("<"); //ここは面倒だ
			printf("'\n");
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		if (token->token_content == NULL)
		{
			printf("minishell: syntax error near unexpected token `<'\n");
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
		ft_lstclear(&preproc_tokens, free_token);
		return (NG);
	}
	ft_lstclear(&preproc_tokens, free_token);
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
		if (parsed_token->cmd == NULL)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			modify_finish_status(shell_list, 258);
			return (NG);
		}
		if (check_greater_than_syntax_error(parsed_token->greater_than, shell_list) == NG)
			return (NG);
		if (check_less_than_syntax_error(parsed_token->less_than, shell_list) == NG)
			return (NG);
		list = list->next;
	}
	return (OK);
}