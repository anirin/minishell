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
		if (token->status != TK_NORMAL && token->status != TK_SPACE) //redirect pipe
		{
			new_token->token_content = ft_strdup(token->token_content);
			if (token->status != TK_DOUBLE_QUOTE && token->status != TK_SINGLE_QUOTE)
				new_token->status = token->status;
			else
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
				tmp = new_content;
				new_content = ft_strjoin(tmp, token->token_content);
				free(tmp);
				tokens = tokens->next;
				if (tokens != NULL)
					token = (t_token *)tokens->content;
			}
			new_token->token_content = ft_strdup(new_content);
			new_token->status = TK_NORMAL;
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
		ft_lstiter(head, &print_token);
		printf("test\n");
	while (head != NULL)
	{
		parsed_token = malloc(sizeof(t_parsed_token));
		parsed_token->greater_than = get_greater_than_tokens(head);
			// ft_lstiter(parsed_token->greater_than, &print_token);
			// printf("get_greater_than_tokens done\n");
		parsed_token->less_than = get_less_than_tokens(head);
			// ft_lstiter(parsed_token->less_than, &print_token);
			// printf("less_than_tokens done\n");
			ft_lstiter(head, &print_token);
			printf("token before cmd\n");
		parsed_token->cmd = get_cmd_tokens(head);
			// ft_lstiter(parsed_token->cmd, &print_token);
			// printf("cmd_tokens done\n");
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
		// ft_lstiter(tokens, &print_token); //print
		// printf("trim_quote done\n\n");
	expand_env(tokens, env_list);
		// ft_lstiter(tokens, &print_token); //print
		// printf("expand done\n\n");
	preproc_tokens = preprocess_tokens(tokens);
		// ft_lstiter(preproc_tokens, &print_token);
		// printf("process done\n\n");
		//free tokens
	ret_tokens = get_list(preproc_tokens);
		ft_lstiter(ret_tokens, &print_parsed_token);
		printf("get_list\n");
	//free prepro_tokens
	return (ret_tokens);
}