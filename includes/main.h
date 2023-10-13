#ifndef MAIN_H
# define MAIN_H

// token
enum		e_token_status
{
	TK_NORMAL,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_DOLL,
	TK_PIPE,
	TK_GREATER_THAN,
	TK_LESS_THAN,
	TK_SPACE,
	TK_USED
};


// builtin

enum		e_builtin_type
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

enum		e_util
{
	UT_SPACE,
	UT_NOT_SPACE,
};

enum		e_redirect
{
	RD_ERROR = 10, //回避方法
	RD_IN,
	RD_OUT,
	RD_HEAEDOC,
	RD_APPEND,
};

# define PATH_SIZE 1024

// readline
# include "libft.h"
# include <ctype.h>
# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/errno.h>
# include <../includes/builtins.h>

typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;

typedef struct s_token
{
	char	*token_content;
	int		status;
}			t_token;

typedef struct s_parsed_token
{
	//リダイレクトを格納
	t_list *greater_than; // token
	t_list *less_than;    // token
	//コマンドを格納
	t_list *cmd;  // token
	t_list *args; // token
}			t_parsed_token;

// lexer
t_list		*lexer(char *line);

//parser
t_list		*preprocess_tokens(t_list *tokens);
t_list		*parser(t_list *tokens, t_list *env_list, t_list *shell_list);

// print
void		print_list(t_list *list);
void		print_arr(char **arr);

// env
t_list		*envp_convert_to_envlist(char **envp);
void		print_list(t_list *list);

// env expand
void		expand_env(t_list *token, t_list *env_list, t_list *shell_list);

// pipefds
int			**malloc_pipefds(t_list *parsed_list);
void		free_pipefds(int **pipefds);

// perse
t_list		*get_greater_than_tokens(t_list *tokens);
t_list		*get_less_than_tokens(t_list *tokens);
t_list		*get_cmd_tokens(t_list *tokens);
t_list		*get_args_tokens(t_list *tokens);
void		move_head(t_list **head);


// exec
void		exec_one_cmd(int *pids, int **pipefds, t_list *parsed_tokens,
				int cmd_index, t_list *env_list);

// util
void		print_env(t_env *env);
void		print_token(t_token *token);
void		print_parsed_token(t_parsed_token *parsed_token);
void		print_lst(void *content);

// void	insort_list(t_list **token, t_list *add_list);
void		insort_list(t_list *token, t_list *add_list);

// builtin
int			is_builtin(t_list *cmd_and_option);

// my_execve
void		my_execve(t_list **env_list, int check, t_list *cmd, t_list *args);

// free
void		free_env(t_env *env);
void		free_token(t_token *token);
void		free_parsed_token(t_parsed_token *parsed_token);
void		free_array(char **array);

// terminate_program.c
void		check_signal(void);
void		terminate_program(int signum, siginfo_t *pid, void *context);

//shell 
void	init_shell_list(t_list **shell_list);
void	wait_for_child_and_store_status(t_list *shell_list, int *pids, int cmd_index);

//syntax
int		check_syntax_error(t_list *list, t_list *token, t_list *shell_list);

#endif