#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

void	my_pwd(void);
void	my_cd(t_list *args);
void	my_echo(t_list *env_list, t_list *cmd, t_list *args);
void	my_env(t_list *env_list, t_list *cmd, t_list *args);
void	my_exit(t_list *env_list, t_list *cmd, t_list *args);
void	my_export(t_list **env_list, t_list *args);
void	my_unset(t_list **env_list, t_list *args);

#endif