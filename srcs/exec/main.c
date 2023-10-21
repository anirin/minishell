#include "libft.h"
#include "main.h"

t_list	*shell_list = NULL;

int g_finish_status; // または他の初期値

int	minishell(char **envp)
{
	char	*line;
	t_list	*tokens;
	t_list	*parsed_tokens;
	t_list	*tmp;
	t_list	*env_list;
	int		*pids;
	int		**pipefds;
	int		cmd_index;
	int		i;

	g_finish_status = 0;
	env_list = envp_convert_to_envlist(envp);
	while (1)
	{
		i = 0;
		cmd_index = 0;
		parent_signal_handler();
		line = readline("\033[32m$>\033[0m ");
		if (line == NULL)
		{
			line = ft_strdup("exit");
		}
		tokens = lexer(line); // free ok)
		parsed_tokens = parser(&tokens, env_list);
		//ここでsyntax error出したい
		if (parsed_tokens == NULL)
			continue ;
		if (check_syntax_error(parsed_tokens, tokens) == NG)
			continue ;
		pids = malloc(sizeof(int) * ft_lstsize(parsed_tokens));
		pipefds = malloc_pipefds(parsed_tokens);
		tmp = parsed_tokens;
		while (tmp != NULL)
		{
			exec_one_cmd(pids, pipefds, tmp, cmd_index, &env_list);
			cmd_index++;
			tmp = tmp->next;
			i++;
		}
		wait_for_child_and_store_status(pids, cmd_index);
		add_history(line);
		free(line);
		free(pids);
		ft_lstclear(&tokens, (void *)free_token);
		ft_lstclear(&parsed_tokens, (void *)free_parsed_token);
		free_pipefds(pipefds);
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
