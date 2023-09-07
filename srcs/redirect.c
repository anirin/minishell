/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:46:34 by atsu              #+#    #+#             */
/*   Updated: 2023/09/08 00:35:16 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	redirect_stdout(t_list *head)
{
	int	fd;

	while (head != NULL && (!(head->status == SPECIAL
				&& ft_strncmp(head->content, "|", 1) == 0)))
	{
		if (head->status == SPECIAL && ft_strncmp(head->content, ">", 2) == 0)
		{
			head = head->next;
			fd = open(head->content, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRWXG | S_IRWXO);
			// printf("out changed fd = %d\n", fd);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (head->status == SPECIAL && ft_strncmp(head->content, ">>",
					3) == 0)
		{
			head = head->next;
			fd = open(head->content, O_WRONLY | O_APPEND | O_CREAT,
					S_IRWXU | S_IRWXG | S_IRWXO);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (head->status == SPECIAL && ft_strncmp(head->content, ">>>",
					4) == 0)
		{
			ft_putendl_fd("minishell : syntax error near unexpected token `>'",
					2);
			exit(258);
		}
		else if (head->status == SPECIAL && ft_strncmp(head->content, ">>>>",
					4) == 0)
		{
			ft_putendl_fd("minishell : syntax error near unexpected token `>>>'",
					2);
			exit(258);
		}
		head = head->next;
	}
}

void	redirect_stdin(t_list *head)
{
	int		fd;
	char	*line;

	while (head != NULL && (!(head->status == SPECIAL
				&& ft_strncmp(head->content, "|", 1) == 0)))
	{
		if (head->status == SPECIAL && ft_strncmp(head->content, "<", 2) == 0)
		{
			head = head->next;
			fd = open(head->content, O_RDONLY);
			// printf("in changed fd = %d\n", fd);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (head->status == SPECIAL && ft_strncmp(head->content, "<<",
					3) == 0)
		{
			head = head->next;
			fd = open(".heardoc_tmp", O_RDWR | O_CREAT | O_TRUNC,
					S_IRWXU | S_IRWXG | S_IRWXO);
			while (line)
			{
				line = readline("heredoc> ");
				if (ft_strncmp(line, head->content,
						ft_strlen(head->content)) == 0)
					break ;
				ft_putendl_fd(line, fd);
				free(line);
				//もしheardocが何個もでできたならtmpファイルは別名にする必要がある
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (head->status == SPECIAL && ft_strncmp(head->content, "<<<",
					3) == 0)
		{
			ft_putendl_fd("minishell : syntax error near unexpected token `<'",
					2);
			exit(258);
		}
		head = head->next;
	}
}

void	find_grater_than_sign_and_redirect(t_list **head)
{
	redirect_stdin(*head);
}

void	find_less_than_sign_and_redirect(t_list **head)
{
	redirect_stdout(*head);
}