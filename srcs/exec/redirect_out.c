/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:45:02 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/04 15:09:26 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

static bool	normal_out(t_token *token)
{
	int	fd;

	fd = open(token->token_content, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
	{
		perror("redirect open ");
		return (false);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (true);
}

static bool	append_out(t_token *token)
{
	int	fd;

	fd = open(token->token_content, O_WRONLY | O_APPEND | O_CREAT,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
	{
		perror("redirect open ");
		return (false);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (true);
}

bool	redirect_out(t_token *token)
{
	if (token->status == RD_OUT && token->token_content != NULL)
	{
		if (normal_out(token) == false)
			return (false);
	}
	else if (token->status == RD_APPEND && token->token_content != NULL)
	{
		if (append_out(token) == false)
			return (false);
	}
	return (true);
}
