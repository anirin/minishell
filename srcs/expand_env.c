/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:53:38 by atsu              #+#    #+#             */
/*   Updated: 2023/09/14 11:25:17 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

char	*find_env_name(char *doller_token, t_env_list *env_list)
{
	if (strlen(doller_token) == 1)
		return (ft_strdup("$"));
	while(env_list != NULL)
	{
		if (env_list->env_value != NULL && ft_strncmp(&doller_token[1], env_list->env_name, ft_strlen(env_list->env_name)+ 1) == 0) //[0] は $
		{
				return (ft_strdup(env_list->env_value));
		}
		env_list = env_list->next;
	}
	return (ft_strdup(""));
}

t_list	*split_by_isspace(char *str)
{
	t_list *splited_env;
	t_list *new;
	char **splited_env_arr;
	int i;
	int count;

	i = 0;
	splited_env = NULL;
	while(1)
	{
		if (str[i] == '\0')
			break ;
		count = 0;
		while (str[i] != '\0' && ft_isspace(str[i]) != 0)
		{
			count++;
			i++;
		}
		if (count > 0)
		{
			new = ft_lstnew(ft_strdup(" "));
			ft_lstadd_back(&splited_env, new);
		}
		count = 0;
		while (str[i] != '\0' && ft_isspace(str[i]) == 0)
		{
			count++;
			i++;
		}
		if (count > 0)
		{
			new = ft_lstnew(ft_substr(str, i - count, count));
			ft_lstadd_back(&splited_env, new);
		}
	}
	return (splited_env);
}

char *parsed_tokens_to_str(t_list *parsed_tokens)
{
	char *ret;
	char *tmp;
	int i;

	i = 0;
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
	char *tmp;

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
			new = ft_lstnew(ft_substr(token, i - count, count));
			ft_lstadd_back(&parsed_tokens, new);
		}
		count = 0;
		if (token[i] == '$')
		{
			i++;
			count++;
			while(token[i] != '\0' && ft_isspace(token[i]) == 0)
			{
				count++;
				i++;
			}
		}
		if (count > 0)
		{
			new = ft_lstnew(ft_substr(token, i - count, count));
			ft_lstadd_back(&parsed_tokens, new);
		}
	}
	return (parsed_tokens);
}

void	expand_env(t_list *token, t_env_list *env_list)
{
	int i;
	char *env_value;
	char *tmp;
	t_list *splited_env;
	t_list *head;
	t_list *lst_tmp;
	t_list *parsed_tokens;

	i = 0;
	while (token != NULL)
	{
		if (ft_strchr(token->content, '$') && token->status == NORMAL)
		{
			lst_tmp = token->next;
			env_value = find_env_name(token->content, env_list);
			splited_env = split_by_isspace(env_value);
			free(env_value);
			if (splited_env == NULL)
			{
				token->content = ft_strdup(" ");
				token->status = NORMAL;
				token->next = lst_tmp;
			}
			while (splited_env != NULL)
			{
				token->content = ft_strdup(splited_env->content);
				token->status = NORMAL; // | を単なる文字として認識させたい
				token->next = lst_tmp;
				splited_env = splited_env->next;
			}
			ft_lstclear(&splited_env, free);
		}
		else if (ft_strchr(token->content, '$') && token->status == DOUBLE_QUOTE) //ここなんかおかしい<-!!
		{
			parsed_tokens = find_dollar_and_parse(token->content);
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
			token->content = parsed_tokens_to_str(head);
			// ft_lstclear(&head, free);
		}
		token = token->next;
	}
}
