/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:32:18 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/30 15:09:21 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_ENV_H
# define EXPAND_ENV_H

# include "libft.h"
# include "main.h"

char	*find_env_name(char *doller_token, t_list *env_list,
			int *finish_status);
char	*parsed_tokens_to_str(t_list *parsed_tokens);
bool	is_heardoc(t_list *prev);
t_list	*find_dollar_and_parse(char *token);
t_list	*split_by_isspace(char *str);
void	expand_env(t_list **token, t_list *env_list, int *finish_status);
void	insort_list(t_list **token, t_list *add_lst, t_list *prev);

#endif