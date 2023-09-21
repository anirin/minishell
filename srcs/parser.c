#include "libft.h"
#include "main.h"

void	lst_trim_quote_iter(t_list *tokens)
{
	char	*tmp;
	t_token *token;

	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
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
		tokens = tokens->next;
	}
}

t_list	*preprocess_tokens(t_list *tokens) //ok
{
	t_list	*prepro_tokens;
	t_list	*new;
	t_token	*token;
	char	*new_token;
	char	*content;
	char	*tmp;

	prepro_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		new_token = NULL;
		if (token->status != TK_NORMAL && token->status != TK_SPACE)
		{
			token->token_content = ft_strdup(token->token_content);
			token->status = TK_NORMAL;
			new = ft_lstnew(token);
			ft_lstadd_back(&prepro_tokens, new);
			tokens = tokens->next;
		}
		else if (token->status == TK_NORMAL)
		{
			new_token = ft_strdup("");
			while (token != NULL && token->status == TK_NORMAL)
			{
				token = (t_token *)tokens->content;
				tmp = new_token;
				new_token = ft_strjoin(tmp, token->token_content);
				free(tmp);
				tokens = tokens->next;
			}
			token->token_content = ft_strdup(new_token);
			token->status = TK_NORMAL;
			new = ft_lstnew(token);
			ft_lstadd_back(&prepro_tokens, new);
		}
	}
	return (prepro_tokens);
}

t_list	*get_list(t_list *tokens)
{
	t_list	*parsed_list;
	t_list	*new;
	t_list	*greater_than_tokens;
	t_list	*less_than_tokens;
	t_list	*cmd_tokens;
	t_list	*head;

	parsed_list = NULL;
	head = tokens;
	while (tokens != NULL)
	{
		greater_than_tokens = get_greater_than_tokens(head);
		less_than_tokens = get_less_than_tokens(head);
		cmd_tokens = get_cmd_tokens(head);
		new = parsed_lstnew(greater_than_tokens, less_than_tokens, cmd_tokens);
		parsed_lstadd_back(&parsed_list, new);
		move_head(&head);
	}
	return (parsed_list);
}

t_list	*parser(t_list *tokens, t_list *env_list)
{
	char **ret;
	t_list *preproc_tokens;
	t_list *ret_tokens;

	ret = NULL;
	lst_trim_quote_iter(tokens);
	expand_env(tokens, env_list);
	preproc_tokens = preprocess_tokens(tokens);
	//free tokens
	ret_tokens = get_list(preproc_tokens);
	//free prepro_tokens
	return (ret_tokens);
}