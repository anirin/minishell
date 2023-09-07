#ifndef MAIN_H
#define MAIN_H

#define NORMAL 0 //space
#define SINGL_QUOTE 1 //'
#define DOUBLE_QUOTE 2 //"
#define FIND_PARETHESES 3 //(
#define FIND_CURLY_BRACKETS 4 //{
#define SPECIAL 5 //|><

//readline
#include <readline/readline.h>
#include <readline/history.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libc.h>

#include "libft.h"

//lexer
t_list	*lexer(char *line);
t_list 	*perxer(t_list *tokens);
void 	print_list(t_list *list);
void 	print_arr(char **arr);
int	 	**count_and_exec_pipe(t_list *tokens);
void	redirect_pipe_stdio(int **pipefds, int exec_num);
void	redirect_stdout(t_list *head);
void	redirect_stdin(t_list *head);
char	**set_cmd(t_list *head);
void	move_head(t_list **head);
void	close_pipefds(int **pipefds);
char	*get_path(char *cmd);


void wait_for_last_two_exec(int *pid, int exec_num, int sataus);
void close_for_last_two_pipefds(int **pipefds, int exec_num);


void free_pipefds(int **pipefds, int exec_num);
void exec_one_readline(t_list **head, int **pipefds, int *pid, int sataus, int exec_num);



#endif