/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:04:23 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 08:46:20 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "lexer.h"

static int	add_space_token_to_list(t_list **list, char *line, int i)
{
	t_list	*new;
	t_token	*token;
	int		space_num;

	space_num = 0;
	while (ft_isspace(line[i]) == 0 && line[i] != '\0')
	{
		space_num++;
		i++;
	}
	if (space_num != 0)
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->token_content = ft_strdup(" ");
		token->status = TK_SPACE;
		new = ft_lstnew(token);
		ft_lstadd_back(list, new);
	}
	return (space_num);
}

static int	add_word_token_to_list(t_list **list, char *line, int i)
{
	int		word_num;
	t_list	*new;
	t_token	*token;

	word_num = 0;
	while (line[i] != '\'' && line[i] != '\"' && line[i] != '\0'
		&& ft_isspace(line[i]) == NOT_SPACE && line[i] != '|' && line[i] != '>'
		&& line[i] != '<' && line[i] != '$')
	{
		i++;
		word_num++;
	}
	if (word_num != 0)
	{
		token = (t_token *)malloc(sizeof(t_token));
		token->token_content = ft_substr(line, i - word_num, word_num);
		token->status = TK_NORMAL;
		new = ft_lstnew(token);
		ft_lstadd_back(list, new);
	}
	return (word_num);
}

static int	add_word_and_space_to_list(t_list **list, char *line, int i)
{
	int	count;

	count = 0;
	count += add_space_token_to_list(list, line, i + count);
	count += add_word_token_to_list(list, line, i + count);
	count += add_space_token_to_list(list, line, i + count);
	return (count);
}

t_list	*lexer(char *line)
{
	int		i;
	t_list	*list;

	i = 0;
	list = NULL;
	while (1)
	{
		if (line[i] == '\0')
			break ;
		if (line[i] == '\'' || line[i] == '\"')
			i += add_quote_token_to_list(&list, line, i, line[i]);
		else if (line[i] == '$')
			i += add_dollar_token_to_list(&list, line, i);
		else if (line[i] == ':')
			i += add_colon_token_to_list(&list, line, i);
		else if (line[i] == '|')
			i += add_pipe_token_to_list(&list, line, i);
		else if (line[i] == '>' || line[i] == '<')
			i += add_redirect_token_to_list(&list, line, i);
		else
			i += add_word_and_space_to_list(&list, line, i);
	}
	return (list);
}
