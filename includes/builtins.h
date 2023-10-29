#ifndef BUILTINS_H
# define BUILTINS_H

# include "stdbool.h"
# include "main.h"

enum	e_Status
{
	SUCCESS,
	FAIL,
};

void	my_pwd(void);
void	my_cd(t_list *env_list, t_list *cmd, t_list *args, int *finish_status);
void	my_echo(t_list *env_list, t_list *cmd, t_list *args);
void	my_env(t_list *env_list, t_list *cmd, t_list *args);
void	my_exit(t_list *env_list, t_list *cmd, t_list *args,
			int *finish_status);
void	my_export(t_list **env_list, t_list *args, int *finish_status);
void	my_unset(t_list **env_list, t_list *args);

//=my_export.c===
int		is_added_env(char *env_name, t_list *env_list);
void	overwrite_env(int env_index, char *env_value, t_list *env_list);
//=my_cd_utils.c==
int		overwrite_pwd(t_list *env_list);
void	to_homedir(t_list *env_list);
int		overwrite_oldpwd(t_list *env_list);
// int		overwrite_oldpwd(t_list *env_list);
// int		overwrite_pwd(t_list *env_list);
// char	*get_env_value(t_list *env_list, char *value_name, int cmd_index);

//exit
int	is_numeric(char *str);
int	is_under_long_max(char *str);

//export
bool	check_export_error(char *str, int *finish_status);
void	append_env(int env_index, char *env_content, t_list *env_list);
void	overwrite_env(int env_index, char *env_value, t_list *env_list);
void	add_env(char **parsed_env, t_list **env_list, int *finish_status);
char	**parse_env(char *token);
t_list	*envp_convert_to_envlist(char **envp);

#endif