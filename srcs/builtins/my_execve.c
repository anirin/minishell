#include "builtins.h"
#include "libft.h"
#include "main.h"

void	my_execve(t_list **env_list, int check, t_list *cmd, t_list *args,
		int *finish_status)
{
	(void)cmd;
	if (check == BT_EXPORT)
	{
		my_export(env_list, args, finish_status);
	}
	if (check == BT_ECHO)
	{
		my_echo(*env_list, cmd, args);
	}
	if (check == BT_ENV)
	{
		my_env(*env_list, cmd, args);
	}
	if (check == BT_EXIT)
	{
		my_exit(*env_list, cmd, args, finish_status);
	}
	if (check == BT_PWD)
	{
		my_pwd();
	}
	if (check == BT_CD)
	{
		my_cd(*env_list, cmd, args, finish_status);
	}
	if (check == BT_UNSET)
	{
		my_unset(env_list, args);
	}
	return ;
}
