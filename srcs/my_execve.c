#include "main.h"
#include "libft.h"

void	my_execve(t_list **env_list, int check, t_list *cmd , t_list *args)
{
	(void)cmd;
	if (check == BT_EXPORT)
	{
		export(env_list, args); //引数もたない
		return ;
	}
}