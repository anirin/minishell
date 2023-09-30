#include "libft.h"
#include "main.h"

void	trim_quote(void *content)
{
	char	*tmp;
	t_token	*token;

	token = (t_token *)content;
	tmp = token->token_content;
	if (token->status == TK_SINGLE_QUOTE)
	{
		token->token_content = ft_strtrim((const char *)tmp, "\'"); //""""のようなケースはないのでOK
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

char	*get_new_content(t_list **tokens)
{
	char	*new_content;
	char	*tmp;
	t_token	*token;

	token = (t_token *)(*tokens)->content;
	if (token->status != TK_NORMAL)
	{
			new_content = ft_strdup(token->token_content);
			*tokens = (*tokens)->next;
	}
	else //if (token->status == TK_NORMAL)
	{
		new_content = ft_strdup("");
		while ((*tokens) != NULL && token != NULL && token->status == TK_NORMAL)
		{
			tmp = new_content;
			new_content = ft_strjoin(tmp, token->token_content);
			free(tmp);
			*tokens = (*tokens)->next;
			if (*tokens != NULL)
				token = (t_token *)(*tokens)->content;
		}
	}
	return (new_content);
}

int		get_new_status(t_list *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	if (token->status != TK_DOUBLE_QUOTE && token->status != TK_SINGLE_QUOTE)
		return (token->status);
	else
		return (TK_NORMAL);
}

t_list	*preprocess_tokens(t_list *tokens) //ok
{
	t_list	*prepro_tokens;
	t_list	*new;
	t_token	*token;
	t_token	*new_token;

	prepro_tokens = NULL;
	while (tokens != NULL)
	{
		// printf("test\n");
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

t_list	*get_list(t_list *tokens)
{
	t_list	*parsed_list;
	t_list	*new;
	t_parsed_token	*parsed_token;
	t_list	*head;

	head = tokens;
	parsed_list = NULL;
	while (head != NULL)
	{
		parsed_token = malloc(sizeof(t_parsed_token));
		parsed_token->less_than = get_less_than_tokens(head);
		parsed_token->greater_than = get_greater_than_tokens(head);
		parsed_token->cmd = get_cmd_tokens(head);
		parsed_token->args = get_args_tokens(head);
		new = ft_lstnew(parsed_token);
		ft_lstadd_back(&parsed_list, new);
		move_head(&head);
	}
	return (parsed_list);
}

t_list	*parser(t_list *tokens, t_list *env_list)
{
	t_list *preproc_tokens;
	t_list *ret_tokens;

	ft_lstiter(tokens, trim_quote);
	expand_env(tokens, env_list);
	preproc_tokens = preprocess_tokens(tokens);
	ret_tokens = get_list(preproc_tokens);
	ft_lstclear(&preproc_tokens, (void *)free_token);
	return (ret_tokens);
}