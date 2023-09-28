#include "libft.h"
#include "main.h"

//コマンドを受けて返すだけのshell
int	minishell(char **envp)
{
	char	*line;
	t_list	*tokens;
	t_list	*parsed_tokens;
	t_list	*env_list;
	int		pids[100];
	int		sataus;
	int		**pipefds;
	int		exec_num;
	int		flag;
	int		cmd_index;

	line = NULL;
	env_list = envp_convert_to_envlist(envp);
	while (1) //二つのコマンドと二つのパイプのみを実行する
	{
		exec_num = 0;
		cmd_index = 0;
		line = readline("$> "); //２回目失敗
		if (strncmp(line, "exit", 4) == 0)
			break ;
		tokens = lexer(line);
			// ft_lstiter(tokens, (void *)print_token);
			// printf("--lexer done--\n");
		parsed_tokens = parser(tokens, env_list);
			//一旦は test |などパイプで終わるケースは無視する
			// ft_lstiter(parsed_tokens, (void *)print_parsed_token);
			// printf("--------\n");
		if (parsed_tokens == NULL)
			continue ;
		pipefds = malloc_pipefds(parsed_tokens);
		while (parsed_tokens != NULL)
		{
			exec_one_cmd(pids, pipefds, parsed_tokens, cmd_index, env_list);
			cmd_index++;
			parsed_tokens = parsed_tokens->next;
		}
		// printf("cmd_index : %d\n", cmd_index);
		while (cmd_index > 0)
		{
			// printf("pid = %d\n", wait(&sataus));
			wait(&sataus);
			cmd_index--;
		}
		add_history(line);
		free(line);
		line = NULL;
		//free tokens
		//free parsed_tokens
		//free pipefds
	}
	//free env
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	minishell(envp);
}