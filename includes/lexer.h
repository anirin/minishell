/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:08:53 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/30 15:09:25 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "main.h"

int	add_colon_token_to_list(t_list **list, char *line, int i);
int	add_dollar_token_to_list(t_list **list, char *line, int i);
int	add_pipe_token_to_list(t_list **list, char *line, int i);
int	add_redirect_token_to_list(t_list **list, char *line, int i);
int	add_quote_token_to_list(t_list **list, char *line, int i, char c);

#endif