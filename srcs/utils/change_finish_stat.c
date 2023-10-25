#include "libft.h"
#include "main.h"

void	wait_for_child_and_store_status(int *pids, int cmd_index,
		int *finish_status)
{
	int cmd_count;
	int status;

	cmd_count = 0;
	// *finish_status = 0;
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
		*finish_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		*finish_status = WTERMSIG(status) + 128;
	}
	else
	{
		printf("aborted");
	}
}