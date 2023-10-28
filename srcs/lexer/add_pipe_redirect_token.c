/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe_redirect_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:04:31 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 08:06:40 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

int	add_pipe_token_to_list(t_list **list, char *line, int i)
{
	t_list	*new;
	t_token	*token;

	(void)line;
	(void)i;
	token = (t_token *)malloc(sizeof(t_token));
	token->token_content = ft_strdup("|");
	token->status = TK_PIPE;
	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
	return (1);
}

int	add_redirect_token_to_list(t_list **list, char *line, int i)
{
	int		word_num;
	t_list	*new;
	t_token	*token;
	char	c;
	int		status;

	if (line[i] == '>')
		status = TK_GREATER_THAN;
	else
		status = TK_LESS_THAN;
	word_num = 0;
	c = line[i];
	while (line[i] == c)
	{
		i++;
		word_num++;
	}
	token = (t_token *)malloc(sizeof(t_token));
	token->token_content = ft_substr(line, i - word_num, word_num);
	token->status = status;
	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
	return (word_num);
}
