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

int	is_biltin(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (EXPORT);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (ECHO);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (CD);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (PWD);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (UNSET);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (ENV);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (EXIT);
	return (-1);
}

int exec_one_readline(t_list **head, int **pipefds, int *pid, int sataus, int exec_num, t_env_list **env_list)
{
	//パイプがない時には親で実行それ以外はこで実行
	char	*path;
	char	**cmd;
	
	// printf("exec_num = %d\n", exec_num);
	if (pipefds != NULL && pipefds[exec_num] != NULL) //もしpipeがあれば
	{
		pipe(pipefds[exec_num]);
		// printf("pipe ok\n");
	}
	//biltin 分岐
	cmd = set_cmd(*head); // コマンドをみつける
	if (is_biltin(cmd[0]) == EXPORT) //exportの場合
	{
		redirect_pipe_stdio(pipefds, exec_num); // パイプを表中ん入力と出力につなぐ
		find_grater_than_sign_and_redirect(head, *env_list); // > を見つける
		find_less_than_sign_and_redirect(head); // < を見つける
		export(env_list, cmd);
		move_head(head);
		if (exec_num - 1 >= 0)
		{
			close (pipefds[exec_num - 1][0]);
			close (pipefds[exec_num - 1][0]);
		}
		return (1);
	}
	pid[exec_num] = fork();
	if(pid[exec_num] == 0) //child
	{
		redirect_pipe_stdio(pipefds, exec_num); // パイプを表中ん入力と出力につなぐ
		find_grater_than_sign_and_redirect(head, *env_list); // < を見つける
		find_less_than_sign_and_redirect(head); // < を見つける
		path = get_path(cmd[0]); // コマンドのパスを探す
		execve(path, cmd, NULL);
		perror(cmd[0]);
		exit(1);
	}
	move_head(head);
	return (0);
}

void wait_exec_and_close_all_pipefds(int **pipefds, int exec_num ,int *sataus, int *pid)
{
	int count = 0;

	while (count < exec_num)
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
		// if (finished_exec_num  < exec_num) //close 後でやる ls | cat の対処
		// {
		// 	close(pipefds[finished_exec_num][0]);
		// 	close(pipefds[finished_exec_num][1]);
		// }
		count++;
	}
}