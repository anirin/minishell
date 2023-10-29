/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_colon_doll_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:04:33 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 08:05:23 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

int	add_colon_token_to_list(t_list **list, char *line, int i)
{
	t_list	*new;
	t_token	*token;
	int		word_num;

	word_num = 0;
	while (1)
	{
		word_num++;
		i++;
		if (line[i] == ':' || line[i] == '$' || line[i] == '\"'
			|| line[i] == '\'' || ft_isspace(line[i]) == UT_SPACE
			|| line[i] == '|' || line[i] == '>' || line[i] == '<'
			|| line[i] == '\0')
		{
			token = (t_token *)malloc(sizeof(t_token));
			token->token_content = ft_substr(line, i - word_num, word_num);
			token->status = TK_NORMAL;
			new = ft_lstnew(token);
			ft_lstadd_back(list, new);
			return (word_num);
		}
	}
	return (-1);
}

static int	check_special_characters(char c)
{
	if (c == '$' || c == '\"' || c == '\'' || ft_isspace(c) == UT_SPACE
		|| c == '|' || c == '>' || c == '<' || c == '\0' || c == ':')
		return (1);
	return (0);
}

static void	add_to_token_list(t_list **list, char *line, int start, int len)
{
	t_list	*new;
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->token_content = ft_substr(line, start, len);
	token->status = TK_DOLL;
	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
}

int	add_dollar_token_to_list(t_list **list, char *line, int i)
{
	int	word_num;

	word_num = 0;
	while (1)
	{
		word_num++;
		i++;
		if (ft_strncmp(&line[i - 1], "$$", 2) == 0)
		{
			word_num++;
			add_to_token_list(list, line, i - 2, 2);
			return (word_num);
		}
		if (check_special_characters(line[i]))
		{
			add_to_token_list(list, line, i - word_num, word_num);
			return (word_num);
		}
	}
	return (-1);
}
