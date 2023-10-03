#include "libft.h"
#include "main.h"

int	minishell(char **envp)
{
	char	*line;
	t_list	*tokens;
	t_list	*parsed_tokens;
	t_list	*tmp;
	t_list	*env_list;
	int		*pids;
	int		sataus;
	int		**pipefds;
	int		cmd_index;

	// struct sigaction	sa;
	line = NULL;
	env_list = envp_convert_to_envlist(envp);
	// ft_lstiter(env_list,(void *)print_env);
	while (1)
	{
		cmd_index = 0;
		line = readline("\033[32m$>\033[0m ");
		if (strncmp(line, "exit", 4) == 0) //いらないbuiltin後
			break ;
		tokens = lexer(line); // free ok
		// ft_lstiter(tokens,(void *)print_token);
		parsed_tokens = parser(tokens, env_list); //ここでsyntax error出したい
													//一旦は test |などパイプで終わるケースは無視する
		// check_syntax_error(parsed_tokens);
		if (parsed_tokens == NULL)
			continue ;
		pids = malloc(sizeof(int) * ft_lstsize(parsed_tokens));
		pipefds = malloc_pipefds(parsed_tokens);
		tmp = parsed_tokens;
		while (tmp != NULL)
		{
			exec_one_cmd(pids, pipefds, tmp, cmd_index, env_list);
			cmd_index++;
			tmp = tmp->next;
		}
		while (cmd_index > 0)
		{
			check_signal();
			wait(&sataus);
			cmd_index--;
		}
		add_history(line);
		free(line);
		free(pids);
		ft_lstclear(&tokens, (void *)free_token);
		ft_lstclear(&parsed_tokens, (void *)free_parsed_token);
		free_pipefds(pipefds);
		//↓親プロセスが実行中にctrl+Cが入力された場合、終了させる関数
		// sigaction(SIGINT,&sa,NULL);
	}
	ft_lstclear(&env_list, (void *)free_env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	minishell(envp);
}