#include "main.h"

void	help_add_token_to_list(t_list **list, char *line, int i, int word_num)
{
	t_list *new;
	char *token;

	token = ft_substr(line, i - word_num + 1, word_num);
	new = ft_lstnew(token);
	ft_lstadd_back(list, new);
}

int		add_token_to_list(t_list **list, char *line, int i, char c)
{
	int word_num;

	word_num = 1;
	if(line[i] == c)
	{
		while(1)
		{
			word_num++;
			i++;
			if (line[i] == '\0')
				break;
			if(line[i] == c)
			{
				help_add_token_to_list(list, line, i, word_num);
				return (word_num + 1);
			}
		}
	}
	return (1);
}

int		add_space_token_to_list(t_list **list, char *line, int i)
{
	t_list *new;
	char *token;
	int		space_num;

	space_num = 0;
	while(isspace(line[i]) && line[i] != '\0')
	{
		space_num++;
		i++;
	}
	if (space_num != 0)
	{
		token = ft_strdup(" ");
		new = ft_lstnew(token);
		ft_lstadd_back(list, new);
	}
	return (space_num);
}

int		add_word_token_to_list(t_list **list, char *line, int i)
{
	int word_num;
	t_list *new;
	char *token;

	word_num = 0;
	while (line[i] != '\'' && line[i] != '\"' 
		&& line[i] != '{' && line[i] != '(' && line[i] != '\0' && isspace(line[i]) == 0)
	{
		i++;
		word_num++;
	}
	if (word_num != 0)
	{
		token = ft_substr(line, i - word_num, word_num);
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
			i += add_token_to_list(&list, line, i, line[i]);
		}
		else if (line[i] == '{')
		{
			i += add_token_to_list(&list, line, i, '}');
		}
		else if (line[i] == '(')
		{
			i += add_token_to_list(&list, line, i, ')');
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