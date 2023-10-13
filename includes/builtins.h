#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

void	my_pwd(void);
void	my_cd(t_list *args);
void	my_echo(t_list *env_list, t_list *cmd, t_list *args);
void	my_env(t_list *env_list, t_list *cmd, t_list *args);
void	my_exit(t_list *env_list, t_list *cmd, t_list *args);
void	my_export(t_list **env_list, t_list *args);

bool	is_accessible(char *new_path, char *input_path);
bool	is_directory(char *new_path, char *input_path);
char	*get_new_path(char *input_path);
char	*trim_last_segment(char *crt_path);

#endif