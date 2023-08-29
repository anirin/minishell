#include "libft.h"
#include "main.h"

//コマンドを受けて返すだけのshell
int	minishell(void)
{
	t_list	*tokens;
	char	*line;
	t_list	*persed_tokens;
	t_list	*head;
	int 	pid;
	char **cmd;
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
		// printf("--first tokens--\n");
		// print_list(tokens);
		persed_tokens = perxer(tokens);
		// printf("--persed tokens--\n");
		// print_list(persed_tokens);
		//exec
		if (persed_tokens == NULL)
			continue ;
		head = persed_tokens;
		pipefds = count_and_exec_pipe(persed_tokens); // | を見つける パイプの数だけpipe()を呼ぶ "は無視する
		while(1)
		{
			pid = fork();
			if (pid == 0) //child
			{
				redirect_pipe_stdio(pipefds, exec_num); // パイプを表中ん入力と出力につなぐ
				// printf("pipe done\n");
				redirect_stdout(head); // < を見つける
				// printf("redirect out done\n");
				redirect_stdin(head); // > を見つける
				// printf("redirect in done\n");
				cmd = set_cmd(head); // コマンドをみつける
				// print_arr(cmd);
				path = get_path(cmd[0]); // コマンドのパスを探す
				// printf("----\n\n");
				execve(path, cmd, NULL);
				perror("execve");
				exit(1);
			}
			exec_num++;
			move_head(&head);
			if (head == NULL)
				break;
		}
		close_pipefds(pipefds);
		// printf("before waitpid\n");
		// while(exec_num-- > 0)
			// waitpid(pid, NULL, 0); //作った子プロセスが終わるまで待つ
		// printf("after waitpid\n");
		add_history(line);
		free(line);
	}
	return (0);
}

int	main(void)
{
	minishell();
}