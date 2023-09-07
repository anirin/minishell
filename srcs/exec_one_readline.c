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
	if (exec_num >= 2) //２つ前のpipeと実行を終了
	{
		close(pipefds[exec_num - 2][0]);
		close(pipefds[exec_num - 2][1]);
		// waitpid(pid[exec_num - 2], &sataus, 0);
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