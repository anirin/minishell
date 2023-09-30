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

char	*find_env_name(char *doller_token, t_list *env_list) //ok
{
	t_env *env;

	if (strlen(doller_token) == 1)
		return (ft_strdup("$"));
	while(env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (env->env_value != NULL && ft_strncmp(&doller_token[1], env->env_name, ft_strlen(env->env_name) + 1) == 0) //[0] は $
		{
				return (ft_strdup(env->env_value));
		}
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}

t_list	*split_by_isspace(char *str)
{
	t_list *splited_env;
	t_list *new;
	t_token *token;
	int i;
	int count;

	i = 0;
	splited_env = NULL;
	while(1)
	{
		if (str[i] == '\0')
			break ;
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

char *parsed_tokens_to_str(t_list *parsed_tokens)
{
	char *ret;
	char *tmp;

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

t_list	*find_dollar_and_parse(char *token)
{
	int i;
	int count;
	t_list *parsed_tokens;
	t_list *new;
	char *str;

	i = 0;
	parsed_tokens = NULL;
	while (token[i] != '\0')
	{
		count = 0;
		while(token[i] != '\0' && token[i] != '$')
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
			while(token[i] != '\0' && ft_isspace(token[i]) == UT_NOT_SPACE && token[i] != '\'' && token[i] != '\"')
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

char	*expand_env_in_str(char *token, t_list *env_list) //ok
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
			parsed_tokens->content = find_env_name(tmp, env_list);
			free(tmp);
		}
		parsed_tokens = parsed_tokens->next;
	}
	ret = parsed_tokens_to_str(head);
	// ft_lstclear(&head, free);
	return (ret);
}

void	expand_env(t_list *token, t_list *env_list) //ok
{
	char *env_value;
	t_list *splited_env;
	t_token *tmp;
	t_token *prev;

	prev = NULL;
	while (token != NULL)
	{
		tmp = (t_token *)token->content;
		if (tmp->status == TK_DOLL && (prev == NULL || (prev != NULL && ft_strncmp(prev->token_content, "<<", 3) == 0)))
		{
			env_value = find_env_name(tmp->token_content, env_list);
			splited_env = split_by_isspace(env_value);
			free(env_value);
			insort_list(token, splited_env); //ok
		}
		else if (ft_strchr(tmp->token_content, '$') && tmp->status == TK_DOUBLE_QUOTE && (prev == NULL || (prev != NULL && ft_strncmp(prev->token_content, "<<", 3) == 0))) 
		{
			tmp->token_content = expand_env_in_str(tmp->token_content, env_list); //ok
			tmp->status = TK_NORMAL;
		}
		prev = (t_token *)token->content;
		token = token->next;
	}
}
