/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:11:22 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 21:14:37 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

static int	is_valid_option(char *option)
{
	int	i;

	i = 1;
	if (ft_strlen(option) == 1)
		return (NG);
	while (option[i] != '\0')
	{
		if (option[i] != 'n')
			return (NG);
		i++;
	}
	return (OK);
}

static int	is_valid_options(t_list *options)
{
	t_token	*option;
	char	*option_str;

	while (options != NULL)
	{
		option = options->content;
		option_str = (char *)option->token_content;
		if (is_valid_option(option_str) == NG)
			return (NG);
		options = options->next;
	}
	return (OK);
}

static int	print_invalid_options(t_list *options)
{
	t_token	*option;
	int		flag;

	flag = NG;
	while (options != NULL)
	{
		option = (t_token *)options->content;
		if (is_valid_option((char *)option->token_content) == OK)
		{
			options = options->next;
		}
		else
			break ;
	}
	while (options != NULL)
	{
		option = (t_token *)options->content;
		printf("%s", (char *)option->token_content);
		flag = OK;
		options = options->next;
		if (options != NULL)
			printf(" ");
	}
	return (flag);
}

static void	print_args(t_list *args)
{
	t_token	*arg;

	while (args != NULL)
	{
		arg = (t_token *)args->content;
		printf("%s", (char *)arg->token_content);
		args = args->next;
		if (args != NULL)
			printf(" ");
	}
}

void	my_echo(t_list *env_list, t_list *cmd, t_list *args)
{
	(void)env_list;
	if (cmd->next == NULL)
	{
		print_args(args);
		printf("\n");
	}
	else
	{
		if (print_invalid_options(cmd->next) == OK && args != NULL)
		{
			printf(" ");
		}
		print_args(args);
		if (is_valid_options(cmd->next) == NG)
		{
			printf("\n");
		}
	}
}
