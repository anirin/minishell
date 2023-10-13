#include "libft.h"
#include "main.h"

void	my_execve(t_list **env_list, int check, t_list *cmd, t_list *args)
{
	(void)cmd;
	if (check == BT_EXPORT)
	{
		export(env_list, args);
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
		my_exit(*env_list, cmd, args);
	}
  else if (check == BT_PWD)
		my_pwd();
  else if (check == BT_CD)
		my_cd();
	return ;
}
