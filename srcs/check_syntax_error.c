#include "libft.h"
#include "main.h"

void	check_greater_than_syntax_error(t_list *greater_than)
{
	t_token *token;

	while (greater_than != NULL)
	{
		token = (t_token *)greater_than->content;
		if (token->status == RD_ERROR)
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);
			ft_putstr_fd(token->token_content, 2);
			ft_putstr_fd("'\n", 2);
			exit(258);
		}
		greater_than = greater_than->next;
	}
}

void	check_syntax_error(t_list *list)
{
	t_list *parsed_token;
	
	while (parsed_token != NULL)
	{
		parsed_token = (t_parsed_token *)list->content;
		check_greater_than_syntax_error(parsed_token->greater_than);
		check_less_than_syntax_error(parsed_token->less_than);
		list = list->next;
	}
}