#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

void	my_cd(t_list *args);
bool	is_accessible(char *new_path, char *input_path);
bool	is_directory(char *new_path, char *input_path);
char	*get_new_path(char *input_path);
char	*trim_last_segment(char *crt_path);

#endif