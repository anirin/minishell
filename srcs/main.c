#include "libft.h"
#include "main.h"

//コマンドを受けて返すだけのshell
int	minishell(char **envp)
{
	t_list	*tokens;
	char	*line;
	t_list	*parsed_tokens;
	t_list	*head;
	t_env_list	*env_list;
	int		pid[100];
	int		sataus;
	int		**pipefds;
	int		exec_num;
	int		flag;

	line = NULL;
	env_list = envp_convert_to_envlist(envp);
	while (1) //二つのコマンドと二つのパイプのみを実行する
	{
		exec_num = 0;
		line = readline("$> ");
		if (strncmp("exit", line, 4) == 0)
		{
			printf("bye!\n");
			exit(0);
		}
		tokens = lexer(line);
		// env_expand_tokens = env_expand(parsed_tokens, env_list);//
		parsed_tokens = parser(tokens);
		if (parsed_tokens == NULL)
			continue ;
		head = parsed_tokens;
		pipefds = count_and_exec_pipe(head);
		while (1)
		{
			flag = exec_one_readline(&head, pipefds, pid, sataus, exec_num, &env_list);
			if (flag == 0)
				exec_num++;
			if (head == NULL)
				break ;
		}
		wait_exec_and_close_all_pipefds(pipefds, exec_num, &sataus, pid);
		add_history(line);
		free(line);
		ft_lstclear(&tokens, free);
		ft_lstclear(&parsed_tokens, free);
	}
	env_lstclear(&env_list, free);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	minishell(envp);
}