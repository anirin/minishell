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
		tokens = lexer(line);
		print_list(tokens);
		parsed_tokens = parser(tokens, env_list);
		print_list(parsed_tokens);
		if (parsed_tokens == NULL)
			continue ;
		pipefds = count_and_exec_pipe(parsed_tokens);
		while (1)
		{
			break ;
		}
		add_history(line);
		free(line);
		//free tokens
		//free parsed_tokens
		//free pipefds
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