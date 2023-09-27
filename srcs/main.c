#include "libft.h"
#include "main.h"

//コマンドを受けて返すだけのshell
int	minishell(char **envp)
{
	char	*line;
	t_list	*tokens;
	t_list	*parsed_tokens;
	t_list	*env_list;
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
		if (strncmp(line, "exit", 4) == 0)
			break ;
		tokens = lexer(line);
			// ft_lstiter(tokens, (void *)print_token);
			// printf("--lexer done--\n");
		parsed_tokens = parser(tokens, env_list);
			//一旦は test |などパイプで終わるケースは無視する
		if (parsed_tokens == NULL)
			continue ;
		pipefds = malloc_pipefds(parsed_tokens);
		while (1)
		{
			// exec_one_cmd(pipefds, parsed_tokens);
			break ;
		}
		add_history(line);
		free(line);
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