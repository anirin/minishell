/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_readline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:27:00 by atsu              #+#    #+#             */
/*   Updated: 2023/09/07 19:07:40y atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

void exec_one_readline(t_list **head, int **pipefds, int *pid, int sataus, int exec_num)
{
	char	*path;
	char	**cmd;
	
	// printf("exec_num = %d\n", exec_num);
	if (pipefds != NULL && pipefds[exec_num] != NULL) //もしpipeがあれば
	{
		pipe(pipefds[exec_num]);
		// printf("pipe ok\n");
	}
	pid[exec_num] = fork();
	if (pid[exec_num] == 0) //child
	{
		redirect_pipe_stdio(pipefds, exec_num); // パイプを表中ん入力と出力につなぐ
		redirect_stdout(*head); // < を見つける
		redirect_stdin(*head); // > を見つける
		cmd = set_cmd(*head); // コマンドをみつける
		path = get_path(cmd[0]); // コマンドのパスを探す
		execve(path, cmd, NULL);
		perror(cmd[0]);
		exit(1);
	}
	move_head(head);
}

void wait_exec_and_close_all_pipefds(int **pipefds, int exec_num ,int *sataus, int *pid)
{
	int count = 0;

	while (count < exec_num) //２つ前のpipeと実行を終了
	{
		char c;
		int finished_pid;
		int finished_exec_num;

		finished_exec_num = 0;
		finished_pid = wait(sataus);
		while(finished_pid != pid[finished_exec_num])
		{
			finished_exec_num++;;
		}
		c = finished_exec_num + '0';
		if (finished_exec_num - 1 >= 0)
		{
			close(pipefds[finished_exec_num - 1][0]);
			close(pipefds[finished_exec_num - 1][1]);
		}
		count++;
	}
}