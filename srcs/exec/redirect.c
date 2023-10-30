/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:47:21 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 20:30:56 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

bool	redirect_in_out(t_list *tokens)
{
	t_token	*token;

	while (tokens != NULL)
	{
		token = (t_token *)tokens->content;
		if (token->status == RD_OUT || token->status == RD_APPEND)
		{
			if (redirect_out(token) == false)
				return (false);
		}
		else if (token->status == RD_IN || token->status == RD_HEAEDOC)
		{
			if (redirect_in(token) == false)
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	redirect(int **pipefds, t_parsed_token *token, int cmd_index)
{
	redirect_pipe(pipefds, cmd_index);
	if (redirect_in_out(token->redirect) == false)
		return (false);
	return (true);
}
