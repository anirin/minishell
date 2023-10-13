#include "libft.h"
#include "main.h"

int		get_greater_than_status(char *str)
{
	if (ft_strlen(str) == 1)
		return (RD_OUT);
	else if (ft_strlen(str) == 2)
		return (RD_APPEND);
	else
		return (RD_ERROR);
}

int		get_less_than_status(char *str)
{
	if (ft_strlen(str) == 1)
		return (RD_IN);
	else if (ft_strlen(str) == 2)
		return (RD_HEAEDOC);
	else
		return (RD_ERROR);
}

char	*get_content(t_list *tokens)
{
	t_token	*token;
	char *ret;

	if (tokens == NULL)
		return (NULL);
	token = (t_token *)tokens->content;
	if (token->status != TK_NORMAL && token->status != TK_DOLL)
		ret = NULL;
	else
	{
		token->status = TK_USED;
		ret = ft_strdup(token->token_content);
	}
	return (ret);
}

void	move_tokens_and_change_status_used(t_list **tokens)
{
	t_token	*token;

	token = (t_token *)(*tokens)->content;
	token->status = TK_USED;
	*tokens = (*tokens)->next;
	if (*tokens == NULL)
		return ;
	else
	{
		token = (t_token *)(*tokens)->content;
		if (token->status == TK_NORMAL)
		{
			token->status = TK_USED;
			*tokens = (*tokens)->next;
		}
	}
}

t_list	*get_greater_than_tokens(t_list *tokens)
{
	t_list	*greater_than_tokens;
	t_token	*token;
	t_token *new;

	greater_than_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == TK_GREATER_THAN)
		{
			new = malloc(sizeof(t_token));
			new->status = get_greater_than_status(token->token_content);
			new->token_content = get_content(tokens->next);
			ft_lstadd_back(&greater_than_tokens, ft_lstnew(new));
			move_tokens_and_change_status_used(&tokens);
		}
		else
		{
			tokens = tokens->next;
		}
		if (token->status == TK_PIPE)
			break;
	}
	return (greater_than_tokens);
}

t_list	*get_less_than_tokens(t_list *tokens)
{
	t_list	*less_than_tokens;
	t_token	*token;
	t_token *new;

	less_than_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == TK_LESS_THAN)
		{
			new = malloc(sizeof(t_token));
			new->status = get_less_than_status(token->token_content);
			new->token_content = get_content(tokens->next);
			ft_lstadd_back(&less_than_tokens, ft_lstnew(new));
			move_tokens_and_change_status_used(&tokens);
		}
		else
		{
			tokens = tokens->next;
		}
		if (token->status == TK_PIPE)
			break;
	}
	return (less_than_tokens);
}

t_list	*get_cmd_tokens(t_list *tokens)
{
	t_list	*cmd_tokens;
	t_token	*token;
	t_token *new;
	int		count;
	
	count = 0;
	cmd_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == TK_PIPE && token->status != TK_USED)
		{
			break ;
		}
		else if (count == 0 || (count >= 1 && token != NULL && token->token_content[0] == '-'))
		{
			new = malloc(sizeof(t_token));
			new->token_content = ft_strdup(token->token_content);
			new->status = TK_NORMAL;
			ft_lstadd_back(&cmd_tokens, ft_lstnew(new));
			token->status = TK_USED;
			count++;
		}
		else
		{
			break ;
		}
		tokens = tokens->next;
	}
	return (cmd_tokens);
}

t_list	*get_args_tokens(t_list *tokens)
{
	t_list	*args_tokens;
	t_token	*token;
	t_token *new;
	
	args_tokens = NULL;
	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status != TK_USED && token->status != TK_PIPE)
		{
			new = malloc(sizeof(t_token));
			new->token_content = ft_strdup(token->token_content);
			new->status = TK_NORMAL;
			ft_lstadd_back(&args_tokens, ft_lstnew(new));
			token->status = TK_USED;
		}
		else if (token->status == TK_PIPE)
		{
			break ;
		}
		tokens = tokens->next;
	}
	return (args_tokens);
}

void	move_head(t_list **head)
{
	t_token	*token;

	while (1)
	{
		if (*head == NULL)
			break ;
		token = (t_token *)(*head)->content;
		if (token->status == TK_PIPE)
		{
			*head = (*head)->next;
			break ;
		}
		*head = (*head)->next;
	}
}