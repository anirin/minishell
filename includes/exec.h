/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:38:43 by atokamot          #+#    #+#             */
/*   Updated: 2023/11/01 13:12:06 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "main.h"

# define PARENT 1
# define CHILD 0

char	**envlist_to_envp(t_list *env_list);
void	exec_builtin_in_child_process(t_list **env_list, int check,
			t_parsed_token *token, int *finish_status);
void	exec_not_builtin_in_child(t_parsed_token *token,
			t_list **env_list);
char	*get_path(t_list *p_cmd_list, t_list *p_env_list, int flag);
void	redirect_pipe(int **pipefds, int cmd_index);
void	close_pipefds(int **pipefds, int cmd_index);
bool	redirect_out(t_token *token);
bool	redirect_in(t_token *token);
bool	redirect(int **pipefds, t_parsed_token *token, int cmd_index);
bool	redirect_in_out(t_list *tokens);
void	close_pipefds(int **pipefds, int cmd_index);
void	redirect_pipe(int **pipefds, int cmd_index);
bool	is_regular_file(char *path);
void	check_cmd_directory_current(char *cmd, int flag);

#endif