#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

void	my_pwd(void);
void	my_cd(t_list *env_list, t_list *cmd, t_list *args);
void	my_echo(t_list *env_list, t_list *cmd, t_list *args);
void	my_env(t_list *env_list, t_list *cmd, t_list *args);
void	my_exit(t_list *env_list, t_list *cmd,
			t_list *args);
void	my_export(t_list **env_list, t_list *args);
void	my_unset(t_list **env_list, t_list *args);

//=my_export.c===
int		is_added_env(char *env_name, t_list *env_list);
void	overwrite_env(int env_index, char *env_value, t_list *env_list);
//=my_cd_utils.c==
void	overwrite_pwd(t_list *env_list);
void	to_homedir(t_list *env_list);
void	overwrite_oldpwd(t_list *env_list);
#endif