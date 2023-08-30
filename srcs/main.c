#include "libft.h"
#include "main.h"

//コマンドを受けて返すだけのshell
int	minishell(void)
{
	t_list	*tokens;
	char	*line;
	t_list	*persed_tokens;
	t_list	*head;
	int 	pid[100];
	int		sataus;
	char	**cmd;
	int		**pipefds;
	int		exec_num;
	char	*path;

	line = NULL;
	exec_num = 0;
	while (1)
	{
		line = readline("$> ");
		if (strncmp("exit", line, 4) == 0)
		{
			printf("bye!\n");
			exit(0);
		}
		tokens = lexer(line);
		persed_tokens = perxer(tokens);
		if (persed_tokens == NULL)
			continue ;
		head = persed_tokens;
		pipefds = count_and_exec_pipe(persed_tokens); // | を見つける パイプの数だけpipe()を呼ぶ "は無視する
		while(1)
		{
			pid[exec_num] = fork();
			if (exec_num >= 2) //パイプを閉じないと永遠にふたつめのcatが標準入力をひきうける
			{
				close(pipefds[exec_num - 2][0]);
				close(pipefds[exec_num - 2][1]);
				waitpid(pid[exec_num - 2], &sataus, 0);
			}
			if (pid[exec_num] == 0) //child
			{
				redirect_pipe_stdio(pipefds, exec_num); // パイプを表中ん入力と出力につなぐ
				redirect_stdout(head); // < を見つける
				redirect_stdin(head); // > を見つける
				cmd = set_cmd(head); // コマンドをみつける
				path = get_path(cmd[0]); // コマンドのパスを探す
				execve(path, cmd, NULL);
				perror(cmd[0]);
				exit(1);
			}
			exec_num++;
			move_head(&head);
			if (head == NULL)
				break;
		}
		close_pipefds(pipefds);
		while (exec_num > 0)
		{
			waitpid(pid[exec_num], &sataus, 0); //重複かも
			exec_num--;
		}
		add_history(line);
		free(line);
	}
	return (0);
}

int	main(void)
{
	minishell();
}