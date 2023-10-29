/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:10:50 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 09:30:06 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "libft.h"
#include "main.h"

t_list	*get_redirect_tokens(t_list *tokens);
t_list	*get_args_tokens(t_list *tokens);
t_list	*get_cmd_tokens(t_list *tokens);
void	move_head(t_list **head);
void	move_tokens_and_change_status_used(t_list **tokens);
char	*get_content(t_list *tokens);
int		get_new_status(t_list *tokens);
char	*get_new_content(t_list **tokens);

#endif
