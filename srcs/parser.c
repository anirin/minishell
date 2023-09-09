#include "libft.h"
#include "main.h"

void	lst_trim_quote_iter(t_list *tokens)
{
	char	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens->content;
		if (tmp[0] == '\"' && tmp[ft_strlen(tmp) - 1] == '\"')
		{
			tokens->content = ft_strtrim((const char *)tmp, "\"");
			free(tmp);
			tokens->status = DOUBLE_QUOTE; //$は即座に展開
		}
		else if (tmp[0] == '\'' && tmp[ft_strlen(tmp) - 1] == '\'')
		{
			tokens->content = ft_strtrim((const char *)tmp, "\'");
			free(tmp);
			tokens->status = SINGL_QUOTE;
		}
		else
		{
			tokens->status = NORMAL;
		}
		tokens = tokens->next;
	}
}

t_list	*preprocess_tokens(t_list *tokens)
{
	t_list	*prepro_tokens;
	t_list	*new;
	char	*new_token;
	char	*content;
	char	*tmp;

	prepro_tokens = NULL;
	while (tokens != NULL)
	{
		new_token = NULL;
		if ((ft_strchr(tokens->content, ' ') != NULL
				|| ft_strchr(tokens->content, '|') != NULL
				|| ft_strchr(tokens->content, '>') != NULL
				|| ft_strchr(tokens->content, '<') != NULL)
			&& tokens->status == NORMAL)
		{
			new_token = strdup(tokens->content);
			new = ft_lstnew(new_token);
			new->status = SPECIAL;
			ft_lstadd_back(&prepro_tokens, new);
			tokens = tokens->next;
		}
		else
		{
			new_token = ft_strdup(tokens->content);
			tokens = tokens->next;
			while (tokens != NULL && ((ft_strchr(tokens->content, ' ') == NULL
						&& ft_strchr(tokens->content, '|') == NULL
						&& ft_strchr(tokens->content, '>') == NULL
						&& ft_strchr(tokens->content, '<') == NULL)
					|| tokens->status != NORMAL))
			{
				tmp = new_token;
				new_token = ft_strjoin(tmp, tokens->content);
				free(tmp);
				tokens = tokens->next;
				if (tokens == NULL)
					break ;
			}
			new = ft_lstnew(new_token);
			new->status = NORMAL;
			ft_lstadd_back(&prepro_tokens, new);
		}
	}
	return (prepro_tokens);
}

t_list	*get_ret_tokens(t_list *tokens)
{
	int		i;
	char	*new_token;
	t_list	*new;
	t_list	*ret_tokens;

	i = 0;
	ret_tokens = NULL;
	while (tokens != NULL)
	{
		if (ft_strncmp(tokens->content, " ", 1) != 0)
		{
			new_token = strdup(tokens->content);
			new = ft_lstnew(new_token);
			new->status = tokens->status;
			ft_lstadd_back(&ret_tokens, new);
			i++;
		}
		tokens = tokens->next;
	}
	return (ret_tokens);
}

t_list *parser(t_list *tokens)
{
	char **ret;
	t_list *preproc_tokens;
	t_list *ret_tokens;

	ret = NULL;
	lst_trim_quote_iter(tokens);
	expand_envvariable(tokens); //$（環境変数）の展開
	preproc_tokens = preprocess_tokens(tokens);
	// printf("--preproc tokens--\n");
	// print_list(preproc_tokens);
	//free tokens
	ret_tokens = get_ret_tokens(preproc_tokens);
	// print_arr(ret);
	//free prepro_tokens
	// printf("--ret tokens--\n");
	// print_list(ret_tokens);
	return (ret_tokens);
}