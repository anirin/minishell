/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quote_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:04:28 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 08:33:01 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

static t_token	*create_token(char *line, int start, int len, int status)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->token_content = ft_substr(line, start, len);
	token->status = status;
	return (token);
}

static void	add_token_to_list(t_list **list, t_token *token)
{
	t_list	*new;

	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
}

static int	get_quote_stat(int c)
{
	int	status;

	if (c == '\'')
		status = TK_SINGLE_QUOTE;
	else
		status = TK_DOUBLE_QUOTE;
	return (status);
}

int	add_quote_token_to_list(t_list **list, char *line, int i, char c)
{
	t_token	*token;
	int		word_num;
	int		status;

	status = get_quote_stat(c);
	word_num = 1;
	while (1)
	{
		word_num++;
		i++;
		if (line[i] == '\0')
		{
			token = create_token(line, i - word_num + 1, word_num, TK_ERROR);
			add_token_to_list(list, token);
			return (word_num - 1);
		}
		else if (line[i] == c)
		{
			token = create_token(line, i - word_num + 1, word_num, status);
			add_token_to_list(list, token);
			return (word_num);
		}
	}
	return (-1);
}
