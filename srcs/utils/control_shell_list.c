#include "libft.h"
#include "main.h"

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

void	wait_for_child_and_store_status(t_list *shell_list, int *pids, int cmd_index)
{
	int 	cmd_count;
	int		status;

	cmd_count = 0;
	while (cmd_count < cmd_index)
	{
		waitpid(pids[cmd_count], &status, 0);
		cmd_count++;
	}
	while(shell_list != NULL)
	{
		if (ft_strncmp(((t_env *)shell_list->content)->name, "?", 2) == 0)
		{
			free(((t_env *)shell_list->content)->value);
			status = WEXITSTATUS(status);
			((t_env *)shell_list->content)->value = ft_itoa(status % 256);
			break ;
		}
		shell_list= shell_list->next;
	}
}