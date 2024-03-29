/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:39:32 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/04 18:37:50 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_env.h"
#include "libft.h"
#include "main.h"

static char	*expand_env_in_str(char *token, t_list *env_list,
		int *finish_status)
{
	t_list	*head;
	t_list	*parsed_tokens;
	char	*tmp;
	char	*ret;

	parsed_tokens = find_dollar_and_parse(token);
	ret = NULL;
	head = parsed_tokens;
	while (parsed_tokens != NULL)
	{
		if (ft_strchr(parsed_tokens->content, '$') != NULL)
		{
			tmp = parsed_tokens->content;
			parsed_tokens->content = find_env_name(tmp, env_list,
					finish_status);
			free(tmp);
		}
		parsed_tokens = parsed_tokens->next;
	}
	ret = parsed_tokens_to_str(head);
	ft_lstclear(&head, free);
	return (ret);
}

static void	handle_dollar(t_list **token, t_list **head, t_list **prev,
		t_expand *expand_data)
{
	char	*env_value;
	t_token	*tmp;
	t_list	*splited_env;
	t_list	*tmp_prev;

	tmp = (t_token *)(*head)->content;
	env_value = find_env_name(tmp->token_content, expand_data->env_list,
			expand_data->finish_status);
	splited_env = split_by_isspace(env_value);
	free(env_value);
	*head = (*head)->next;
	tmp_prev = ft_lstlast(splited_env);
	insort_list(token, splited_env, *prev);
	*prev = tmp_prev;
}

static void	handle_double_quote(t_list **head, t_list *env_list, t_list **prev,
		int *finish_status)
{
	t_token	*tmp;
	char	*tmp_str;

	tmp = (t_token *)(*head)->content;
	tmp_str = tmp->token_content;
	tmp->token_content = expand_env_in_str(tmp->token_content, env_list,
			finish_status);
	free(tmp_str);
	tmp->status = TK_NORMAL;
	*prev = *head;
	*head = (*head)->next;
}

static void	help_expand_env(t_list **prev, t_list **prev_prev, t_list **head)
{
	*prev_prev = *prev;
	*prev = *head;
	*head = (*head)->next;
}

void	expand_env(t_list **token, t_list *env_list, int *finish_status)
{
	t_list		*head;
	t_list		*prev;
	t_list		*prev_prev;
	t_token		*tmp;
	t_expand	expand_data;

	expand_data.env_list = env_list;
	expand_data.finish_status = finish_status;
	prev = NULL;
	prev_prev = NULL;
	head = *token;
	while (head)
	{
		tmp = (t_token *)head->content;
		if (tmp->status == TK_DOLL && is_heardoc(prev, prev_prev) == false)
			handle_dollar(token, &head, &prev, &expand_data);
		else if (ft_strchr(tmp->token_content, '$')
			&& tmp->status == TK_DOUBLE_QUOTE && is_heardoc(prev,
				prev_prev) == false)
			handle_double_quote(&head, env_list, &prev, finish_status);
		else
			help_expand_env(&prev, &prev_prev, &head);
	}
}
