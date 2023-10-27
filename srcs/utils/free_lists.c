/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakaiheizou <nakaiheizou@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:53:05 by nakaiheizou       #+#    #+#             */
/*   Updated: 2023/10/27 17:57:31 by nakaiheizou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void	free_token(t_token *token)
{
	free(token->token_content);
	free(token);
}

void	free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

void	free_parsed_token(t_parsed_token *parsed_token)
{
	ft_lstclear(&parsed_token->redirect, (void *)free_token);
	ft_lstclear(&parsed_token->cmd, (void *)free_token);
	ft_lstclear(&parsed_token->args, (void *)free_token);
	free(parsed_token);
}
