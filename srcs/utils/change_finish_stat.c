#include "libft.h"
#include "main.h"

void	wait_for_child_and_store_status(int *pids, int cmd_index)
{
	int cmd_count;
	int status;

	cmd_count = 0;
	while (cmd_count < cmd_index)
	{
		child_signal_handler();
		if (pids[cmd_count] < 0)
		{
			return ;
		}
		else
		{
			waitpid(pids[cmd_count], &status, 0);
		}
		cmd_count++;
	}
	if (WIFEXITED(status))
	{
		g_finish_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		g_finish_status = WTERMSIG(status) + 128;
	}
	else
	{
		printf("aborted");
	}
}