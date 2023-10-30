/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakai <hnakai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:10:45 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/30 17:15:30 by hnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "builtins.h"
# include <ctype.h>
# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>

extern int			g_signal_flag;

// token
enum				e_token_status
{
	TK_NORMAL,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_DOLL,
	TK_PIPE,
	TK_GREATER_THAN,
	TK_LESS_THAN,
	TK_SPACE,
	TK_ENV_SPACE,
	TK_USED,
	TK_ERROR
};

// builtin

enum				e_builtin_type
{
	BT_EXPORT,
	BT_ECHO,
	BT_CD,
	BT_PWD,
	BT_UNSET,
	BT_ENV,
	BT_EXIT,
	BT_NOTBUILTIN
};

// util

enum				e_util
{
	UT_SPACE,
	UT_NOT_SPACE,
};

enum				e_redirect
{
	RD_IN_ERROR = 10,
	RD_OUT_ERROR,
	RD_IN,
	RD_OUT,
	RD_HEAEDOC,
	RD_APPEND,
};

enum				e_signal
{
	PARENT_SIGINT,
	PARENT_SIGQUIT,
	CHILD_SIGINT,
	CHILD_SIGQUIT,
};

# define PATH_SIZE 1024

typedef struct s_env
{
	char			*name;
	char			*value;
}					t_env;

typedef struct s_token
{
	char			*token_content;
	int				status;
}					t_token;

typedef struct s_parsed_token
{
	t_list			*redirect;
	t_list			*cmd;
	t_list			*args;
}					t_parsed_token;

typedef struct s_exec
{
	t_list			**env_list;
	int				cmd_index;
	int				*pids;
	int				**pipefds;
	t_parsed_token	*token;
}					t_exec;

// lexer
t_list				*lexer(char *line);

// parser
t_list				*preprocess_tokens(t_list *tokens);
t_list				*parser(t_list **tokens, t_list *env_list,
						int *finish_status);

// print
void				print_list(t_list *list);
void				print_arr(char **arr);

// env
t_list				*envp_convert_to_envlist(char **envp);
void				print_list(t_list *list);
void				update_env_end(char *path, t_list **env_list);

// env expand
void				expand_env(t_list **token, t_list *env_list,
						int *finish_status);

// pipefds
int					**malloc_pipefds(t_list *parsed_list);
void				free_pipefds(int **pipefds);

// exec
void				exec_one_cmd(t_exec *data, t_list *parsed_tokens,
						int *finish_status);

// builtin
int					is_builtin(t_list *cmd_and_option);

// my_execve
void				my_execve(t_list **env_list, int check,
						t_parsed_token *token, int *finish_status);

// free
void				free_env(t_env *env);
void				free_token(t_token *token);
void				free_parsed_token(t_parsed_token *parsed_token);
void				free_array(char **array);

// terminate
void				parent_signal_handler(int *finish_status);
void				child_signal_handler(void);

// shell
void				wait_for_child_and_store_status(int *pids, int cmd_index,
						int *finish_status);

// syntax
int					check_syntax_error(t_list *list, t_list *token,
						int *finish_status);
void				change_finish_status(int g_signal_flag, int *finish_status);

// error
void				print_err(char *cmd, char *str);

#endif