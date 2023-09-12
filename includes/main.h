#ifndef MAIN_H
# define MAIN_H

# define NORMAL 0              //space
# define SINGL_QUOTE 1         //'
# define DOUBLE_QUOTE 2        //"
# define FIND_PARETHESES 3     //(
# define FIND_CURLY_BRACKETS 4 //{
# define SPECIAL 5             //|><

# define EXPORT 0
# define ECHO 1
# define CD 2
# define PWD 3
# define UNSET 4
# define ENV 5
# define EXIT 6

//readline
# include "libft.h"
# include <ctype.h>
# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//lexer
t_list	*lexer(char *line);
t_list	*parser(t_list *tokens);

//print
void	print_list(t_list *list);
void	print_arr(char **arr);

//exec
int		**count_and_exec_pipe(t_list *tokens);
void	redirect_pipe_stdio(int **pipefds, int exec_num);
char	**set_cmd(t_list *head);
void	move_head(t_list **head);
void	close_pipefds(int **pipefds);
char	*get_path(char *cmd);
void	wait_for_last_two_exec(int *pid, int exec_num, int sataus);
void	close_for_last_two_pipefds(int **pipefds, int exec_num);
void	free_pipefds(int **pipefds, int exec_num);
int		exec_one_readline(t_list **head, int **pipefds, int *pid, int sataus,
			int exec_num, t_list **env_list);
void	wait_exec_and_close_all_pipefds(int **pipefds, int exec_num,
			int *sataus, int *pid);

//redirect
void	find_grater_than_sign_and_redirect(t_list **head);
void	find_less_than_sign_and_redirect(t_list **head);
//out
void	redirect_stdout(t_list *head);
void	append_redirect_stdout(t_list *head);
//in
void	redirect_stdin(t_list *head);
void	heardocument(t_list *head);

//env
void export(t_list **env_list, char **cmd);
t_list	*envp_convert_to_linearlist(char **envp);

#endif