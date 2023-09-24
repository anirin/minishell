#include "libft.h"
#include "main.h"

t_list	*get_greater_than_tokens(t_list *tokens)
{
	t_list	*greater_than_tokens;
	t_token	*token;
	t_token *new;

	greater_than_tokens = NULL;
	while (tokens != NULL)
	{
		new = malloc(sizeof(t_token));
		token = (t_token *)tokens->content;
		if (token->status == TK_GREATER_THAN)
		{
			if (ft_strlen(token->token_content) == 1)
				new->status = RD_OUT;
			else if (ft_strlen(token->token_content) == 2)
				new->status = RD_APPEND;
			else
				new->status = RD_ERROR;
			token->status = TK_USED;
			tokens = tokens->next;
			if (tokens == NULL)
				token = NULL;
			else
				token = (t_token *)tokens->content;
			if (token == NULL || token->status != TK_NORMAL)
			{
				new->token_content = NULL;
				ft_lstadd_back(&greater_than_tokens, ft_lstnew(new));
			}
			else
			{
				token->status = TK_USED;
				new->token_content = ft_strdup(token->token_content);
				ft_lstadd_back(&greater_than_tokens, ft_lstnew(new));
			}
		}
		if (token->status == TK_PIPE)
			break ;
		tokens = tokens->next;
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
		new = malloc(sizeof(t_token));
		token = (t_token *)tokens->content;
		if (token->status == TK_LESS_THAN)
		{
			if (ft_strlen(token->token_content) == 1)
				new->status = RD_IN;
			else if (ft_strlen(token->token_content) == 2)
				new->status = RD_HEAEDOC;
			else
				new->status = RD_ERROR;
			token->status = TK_USED;
			tokens = tokens->next;
			if (tokens == NULL)
				token = NULL;
			else
				token = (t_token *)tokens->content;
			if (token == NULL || token->status != TK_NORMAL)
			{
				new->token_content = NULL;
				ft_lstadd_back(&less_than_tokens, ft_lstnew(new));
			}
			else
			{
				token->status = TK_USED;
				new->token_content = ft_strdup(token->token_content);
				ft_lstadd_back(&less_than_tokens, ft_lstnew(new));
			}
		}
		if (token->status == TK_PIPE)
			break ;
		tokens = tokens->next;
	}
	return (less_than_tokens);
}

t_list	*get_cmd_tokens(t_list *tokens)
{
	t_list	*cmd_tokens;
	t_token	*token;
	t_token *new;
	
	cmd_tokens = NULL;
	while (tokens != NULL)
	{
		new = malloc(sizeof(t_token));
		token = (t_token *)tokens->content;
		if (token->status != TK_USED && token->status != TK_PIPE)
		{
			new->token_content = ft_strdup(token->token_content);
			new->status = TK_NORMAL;
			ft_lstadd_back(&cmd_tokens, ft_lstnew(new));
			token->status = TK_USED;
		}
		else if (token->status == TK_PIPE)
		{
			break ;
		}
		tokens = tokens->next;
	}
	return (cmd_tokens);
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