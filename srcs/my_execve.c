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
	// else if (check == BT_ECHO)
	// 	my_echo();
	// else if (check == BT_CD)
	// 	my_cd();
	// else if (check == BT_PWD)
	// 	my_pwd(env_list);
	// else if (check == BT_UNSET)
	// 	my_unset();
	// else if (check == BT_ENV)
	// 	my_env();
	// else if (check == BT_EXIT)
	// 	my_exit();
}

// void	my_pwd(t_list **env_list)
// {
// 	while (ft_strncmp((*env_list)->content->env_name, "PWD", 3) == 0)
// 	{
// 		(*env_list) = (*env_list)->next;
// 	}
// 	printf("");
// }
