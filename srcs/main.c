#include "libft.h"
#include "main.h"

int	minishell(char **envp)
{
	char	*line;
	t_list	*tokens;
	t_list	*parsed_tokens;
	t_list	*tmp;
	t_list	*env_list;
	t_list	*shell_list;
	int		*pids;
	int		**pipefds;
	int		cmd_index;

	line = NULL;
	env_list = envp_convert_to_envlist(envp);
	init_shell_list(&shell_list);
	while (1)
	{
		cmd_index = 0;
		line = readline("\033[32m$>\033[0m ");
		tokens = lexer(line); //free ok
		parsed_tokens = parser(tokens, env_list, shell_list); //ここでsyntax error出したい
			//一旦は test |などパイプで終わるケースは無視する
		//check_syntax_error(parsed_tokens);
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
		wait_for_child_and_store_status(shell_list, pids, cmd_index);
			ft_lstiter(shell_list, (void *)print_env);
		add_history(line);
		free(line);
		free(pids);
		ft_lstclear(&tokens, (void *)free_token);
		ft_lstclear(&parsed_tokens, (void *)free_parsed_token);
		free_pipefds(pipefds);
	}
	ft_lstclear(&env_list, (void *)free_env);
	ft_lstclear(&shell_list, (void *)free_env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	minishell(envp);
}