#include "main.h"

int		add_quote_token_to_list(t_list **list, char *line, int i, char c)
{
	t_list *new;
	t_token *token;
	int word_num;
	int status;

	if (c == '\'')
		status = TK_SINGLE_QUOTE;
	else
		status = TK_DOUBLE_QUOTE;
	word_num = 1;  //' or "の分
	while(1)
	{
		word_num++;
		i++;
		if(line[i] == c)
		{
			token->token_content = ft_substr(line, i - word_num + 1, word_num);
			token->status = status;
			new = ft_lstnew(token);
			ft_lstadd_back(list, new);
			return (word_num);
		}
	}
	return (-1);
}

int		add_dollar_token_to_list(t_list **list, char *line, int i)
{
	t_list *new;
	t_token *token;
	int word_num;

	word_num = 0;
	while(1)
	{
		word_num++;
		i++;
		if(line[i] == '\"' || line[i] == '\'' || ft_isspace(line[i]) == 1 || line[i] == '|' || line[i] == '>' || line[i] == '<' || line[i] == '\0')
		{
			token->token_content = ft_substr(line, i - word_num + 1, word_num);
			token->status = TK_DOLL;
			new = ft_lstnew(token);
			ft_lstadd_back(list, new);
			return (word_num);
		}
	}
	return (-1);
}

int		add_space_token_to_list(t_list **list, char *line, int i)
{
	t_list *new;
	t_token *token;
	int		space_num;

	space_num = 0;
	while(ft_isspace(line[i]) == SPACE && line[i] != '\0')
	{
		space_num++;
		i++;
	}
	if (space_num != 0)
	{
		token->token_content = ft_strdup(" ");
		token->status = TK_SPACE;
		new = ft_lstnew(token);
		ft_lstadd_back(list, new);
	}
	return (space_num);
}

int		add_pipe_token_to_list(t_list **list, char *line, int i)
{
	int word_num;
	t_list *new;
	t_token *token;
	char c;

	word_num = 0;
	token->token_content = strdup("|");
	token->status = TK_PIPE;
	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
	return (1);
}

int		add_redirect_token_to_list(t_list **list, char *line, int i)
{
	int word_num;
	t_list *new;
	t_token *token;
	char c;
	int status;

	if (line[i] == '>')
		status = TK_GREATER_THAN;
	else
		status = TK_LESS_THAN;
	word_num = 0;
	c = line[i];
	while(line[i] == c)
	{
		i++;
		word_num++;
	}
	token->token_content = ft_substr(line, i - word_num, word_num);
	token->status = status;
	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
	return (word_num);
}

int		add_word_token_to_list(t_list **list, char *line, int i)
{
	int word_num;
	t_list *new;
	t_token *token;

	word_num = 0;
	while (line[i] != '\'' && line[i] != '\"' && line[i] != '\0'
		&& ft_isspace(line[i]) == NOT_SPACE && line[i] != '|' && line[i] != '>' && line[i] != '<' && line[i] != '$')
	{
		i++;
		word_num++;
	}
	if (word_num != 0)
	{
		token->token_content = ft_substr(line, i - word_num, word_num);
		token->status = TK_NORMAL; 
		new = ft_lstnew(token);
		ft_lstadd_back(list, new);
	}
	return (word_num);
}

t_list	*lexer(char *line)
{
	int i;
	int word_num;
	int status;
	t_list *list;

	i = 0;
	word_num = 0;
	list = NULL;

	while (1)
	{
		if (line[i] == '\0')
			break ;
		if (line[i] == '\'' || line[i] == '\"')
		{
			i += add_quote_token_to_list(&list, line, i, line[i]);
		}
		else if (line[i] == '$')
		{
			i += add_dollar_token_to_list(&list, line, i);
		}
		else if (line[i] == '|')
		{
			i += add_pipe_token_to_list(&list, line, i);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			i += add_redirect_token_to_list(&list, line, i);
		}
		else
		{
			i += add_space_token_to_list(&list, line, i);
			i += add_word_token_to_list(&list, line, i);
			i += add_space_token_to_list(&list, line, i);
		}
	}
	return (list);
}