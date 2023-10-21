#include "libft.h"
#include "main.h"

void	modify_finish_status(t_list *shell_list, int status)
{
	t_env	*shell;

	shell = (t_env *)shell_list->content;
	free(shell->value);
	shell->value = ft_itoa(status);
}

void	init_shell_list(t_list **shell_list)
{
	t_env	*shell;
	t_list	*new;

	*shell_list = NULL;
	shell = (t_env *)malloc(sizeof(t_env));
	shell->name = ft_strdup("?");
	shell->value = ft_strdup("0");
	new = ft_lstnew(shell);
	ft_lstadd_back(shell_list, new);
}

void	wait_for_child_and_store_status(int *pids, int cmd_index)
{
	int 	cmd_count;
	int		status;

	cmd_count = 0;
	while (cmd_count < cmd_index)
	{
		waitpid(pids[cmd_count], &status, 0);
		cmd_count++;
	}
	status = WEXITSTATUS(status);
	g_finish_status = status % 256;
}