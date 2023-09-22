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

t_list	*preprocess_tokens(t_list *tokens) //ok
{
	t_list	*prepro_tokens;
	t_list	*new;
	t_token	*token;
	t_token	*new_token;
	char	*new_content;
	char	*content;
	char	*tmp;

	prepro_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		new_token = (t_token *)malloc(sizeof(t_token));
		if (token->status != TK_NORMAL && token->status != TK_SPACE)
		{
			new_token->token_content = ft_strdup(token->token_content);
			new_token->status = TK_NORMAL;
			new = ft_lstnew(new_token);
			ft_lstadd_back(&prepro_tokens, new);
			tokens = tokens->next;
		}
		else if (token->status == TK_NORMAL)
		{
			new_content = ft_strdup("");
			while (tokens != NULL && token != NULL && token->status == TK_NORMAL)
			{
				token = (t_token *)tokens->content;//??
				tmp = new_content;
				new_token = ft_strjoin(tmp, token->token_content);
				free(tmp);
				tokens = tokens->next;
			}
			new_token->token_content = ft_strdup(new_token);
			new_token->status = TK_NORMAL;
			new = ft_lstnew(new_token);
			ft_lstadd_back(&prepro_tokens, new);
		}
	}
	return (prepro_tokens);
}

t_list	*get_list(t_list *tokens)
{
	t_list	*parsed_list;
	t_list	*new;
	t_parsed_token	*parsed_token;
	t_list	*head;

	parsed_list = NULL;
	head = tokens;
	while (tokens != NULL)
	{
		parsed_token->greater_than = get_greater_than_tokens(head);
		parsed_token->less_than = get_less_than_tokens(head);
		parsed_token->cmd = get_cmd_tokens(head);
		new = ft_lstnew(parsed_token);
		ft_lstadd_back(&parsed_list, new);
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
	ft_lstiter(tokens, trim_quote);
	// ft_lstiter(tokens, &print_token);
	printf("trim_quote\n");
	expand_env(tokens, env_list);
	printf("expand_env\n");
	// ft_lstiter(tokens, &print_token);
	preproc_tokens = preprocess_tokens(tokens);
	printf("preprocess_tokens\n");
	ft_lstiter(tokens, &print_token);
	printf("-------------\nend\n");
	//free tokens
	ret_tokens = get_list(preproc_tokens);
	printf("get_list\n");
	//free prepro_tokens
	return (ret_tokens);
}