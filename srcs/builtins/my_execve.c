#include "libft.h"
#include "main.h"

void	my_execve(t_list **env_list, int check, t_list *cmd, t_list *args)
{
	(void)cmd;
	if (check == BT_EXPORT)
	{
		export(env_list, args);
		return ;
	}
	// printf("cmd : %s\n", (char *)cmd->content);
	// else if (check == BT_ECHO)
	// 	my_echo();
	else if (check == BT_CD)
		my_cd(args);
	else if (check == BT_PWD)
		my_pwd();
	// else if (check == BT_UNSET)
	// 	my_unset();
	// else if (check == BT_ENV)
	// 	my_env();
	// else if (check == BT_EXIT)
	// 	my_exit();
}
