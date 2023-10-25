/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:53:38 by atsu              #+#    #+#             */
/*   Updated: 2023/09/24 20:41:37by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

// 終了ステータスはfinish_statusに格納する
static char	*find_env_name(char *doller_token, t_list *env_list,
							int *finish_status) // ok
{
	t_env *env;
	t_env *shell;

	if (strlen(doller_token) == 1)
		return (ft_strdup("$"));
	if (ft_strncmp(&doller_token[1], "?", 2) == 0)
		return (ft_itoa(*finish_status));
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (env->value != NULL && ft_strncmp(&doller_token[1], env->name,
				ft_strlen(env->name) + 1) == 0)
		{
			return (ft_strdup(env->value));
		}
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}

static t_list	*split_by_isspace(char *str)
{
	t_list	*splited_env;
	t_list	*new;
	t_token	*token;
	int		i;
	int		count;

	i = 0;
	splited_env = NULL;
	while (1)
	{
		if (str[i] == '\0')
		{
			token = malloc(sizeof(t_token));
			token->token_content = ft_strdup(" ");
			token->status = TK_SPACE;
			new = ft_lstnew(token);
			ft_lstadd_back(&splited_env, new);
			break ;
		}
		count = 0;
		while (str[i] != '\0' && ft_isspace(str[i]) == UT_SPACE)
		{
			count++;
			i++;
		}
		if (count > 0)
		{
			token = malloc(sizeof(t_token));
			token->token_content = ft_strdup(" ");
			token->status = TK_SPACE;
			new = ft_lstnew(token);
			ft_lstadd_back(&splited_env, new);
		}
		count = 0;
		while (str[i] != '\0' && ft_isspace(str[i]) == UT_NOT_SPACE)
		{
			count++;
			i++;
		}
		if (count > 0)
		{
			token = malloc(sizeof(t_token));
			token->token_content = ft_substr(str, i - count, count);
			token->status = TK_NORMAL;
			new = ft_lstnew(token);
			ft_lstadd_back(&splited_env, new);
		}
	}
	return (splited_env);
}

static char	*parsed_tokens_to_str(t_list *parsed_tokens)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	while (parsed_tokens != NULL)
	{
		tmp = ret;
		ret = ft_strjoin(tmp, parsed_tokens->content);
		free(tmp);
		parsed_tokens = parsed_tokens->next;
	}
	return (ret);
}

static t_list	*find_dollar_and_parse(char *token)
{
	int		i;
	int		count;
	t_list	*parsed_tokens;
	t_list	*new;
	char	*str;

	i = 0;
	parsed_tokens = NULL;
	while (token[i] != '\0')
	{
		count = 0;
		while (token[i] != '\0' && token[i] != '$')
		{
			count++;
			i++;
		}
		if (count > 0)
		{
			str = ft_substr(token, i - count, count);
			new = ft_lstnew(str);
			ft_lstadd_back(&parsed_tokens, new);
		}
		count = 0;
		if (token[i] == '$')
		{
			i++;
			count++;
			while (token[i] != '\0' && ft_isspace(token[i]) == UT_NOT_SPACE
				&& token[i] != '\'' && token[i] != '\"')
			{
				count++;
				i++;
			}
		}
		if (count > 0)
		{
			str = ft_substr(token, i - count, count);
			new = ft_lstnew(str);
			ft_lstadd_back(&parsed_tokens, new);
		}
	}
	return (parsed_tokens);
}

static char	*expand_env_in_str(char *token, t_list *env_list, int *finish_status)
// ok
{
	t_list *head;
	t_list *parsed_tokens;
	char *tmp;
	char *ret;

	parsed_tokens = find_dollar_and_parse(token);
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
	// ft_lstclear(&head, free);
	return (ret);
}

bool	is_heardoc(t_list *prev)
{
	t_token	*token;

	if (prev == NULL)
		return (false);
	token = (t_token *)prev->content;
	if (ft_strncmp(token->token_content, "<<", 3) == 0)
		return (true);
	return (false);
}

void	expand_env(t_list **token, t_list *env_list, int *finish_status) // ok
{
	char *env_value;
	t_list *splited_env;
	t_token *tmp;

	t_list *prev;
	t_list *tmp_prev;

	t_list *head;

	prev = NULL;
	head = *token;
	while (head != NULL)
	{
		tmp = (t_token *)head->content;
		if (tmp->status == TK_DOLL && is_heardoc(prev) == false)
		{
			env_value = find_env_name(tmp->token_content, env_list,
					finish_status);
			splited_env = split_by_isspace(env_value);
			free(env_value);
			head = head->next;
			tmp_prev = ft_lstlast(splited_env);
			insort_list(token, splited_env, prev); // ok
			prev = tmp_prev;
		}
		else if (ft_strchr(tmp->token_content, '$')
			&& tmp->status == TK_DOUBLE_QUOTE && is_heardoc(prev) == false)
		{
			tmp->token_content = expand_env_in_str(tmp->token_content, env_list,
					finish_status); // ok
			tmp->status = TK_NORMAL;
			prev = head;
			head = head->next;
		}
		else
		{
			prev = head;
			head = head->next;
		}
	}
}
