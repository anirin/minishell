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

	less_than_tokens = NULL;
	while (tokens != NULL)
	{
		if (tokens->status == LESS_THAN)
		{
			less_than_tokens = ft_lstnew(ft_strdup(tokens->content),
					LESS_THAN);
			tokens = tokens->next;
			tokens->status = USED;
			if (tokens != NULL && tokens->status == NORMAL)
			{
				less_than_tokens->next = ft_lstnew(ft_strdup(tokens->next->content),
						LESS_THAN);
				tokens = tokens->next;
				tokens->status = USED;
			}
		}
		else if (tokens->status == PIPE)
		{
			break ;
		}
		tokens = tokens->next;
	}
	return (less_than_tokens);
}

t_list	*get_cmd_tokens(t_list *tokens)
{
	t_list	*cmd_tokens;

	cmd_tokens = NULL;
	while (tokens != NULL)
	{
		if (tokens->status == NORMAL)
		{
			cmd_tokens = ft_lstnew(ft_strdup(tokens->content), NORMAL);
			tokens->status = USED;
			tokens = tokens->next;
		}
		else if (tokens->status == PIPE)
		{
			break ;
		}
		if (tokens == NULL)
			break ;
		tokens = tokens->next;
	}
	return (cmd_tokens);
}

void	move_head(t_list **head)
{
	while (*head != NULL && (*head)->status != PIPE)
	{
		*head = (*head)->next;
	}
}