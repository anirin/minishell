/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:44:56 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 20:32:56 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

static bool	normal_in(t_token *token)
{
	int	fd;

	fd = open(token->token_content, O_RDONLY);
	if (fd == -1)
	{
		perror("redirect open");
		return (false);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (true);
}

static void	close_unlink_dup(int fd)
{
	close(fd);
	open(".heardoc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".heardoc");
}

static bool	heardoc_in(t_token *token)
{
	int		fd;
	char	*line;

	fd = open(".heardoc", O_RDWR | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
	{
		perror("redirect open");
		return (false);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			exit(1);
		if (ft_strncmp(line, token->token_content,
				ft_strlen(token->token_content) + 1) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close_unlink_dup(fd);
	return (true);
}

bool	redirect_in(t_token *token)
{
	if (token->status == RD_IN && token->token_content != NULL)
	{
		if (normal_in(token) == false)
			return (false);
	}
	else if (token->status == RD_HEAEDOC && token->token_content != NULL)
	{
		if (heardoc_in(token) == false)
			return (false);
	}
	return (true);
}
