#include "libft.h"
#include "main.h"

int	signal_flag = 0;

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
	int		*finish_status;
	int		i;

	finish_status = (int *)malloc(sizeof(int) * 2);
	*finish_status = 0;
	signal_flag = -1;
	env_list = envp_convert_to_envlist(envp);
	while (1)
	{
		i = 0;
		cmd_index = 0;
		signal_flag = -1;
		parent_signal_handler(finish_status);
		line = readline("\033[32m$>\033[0m ");
		change_finish_status(signal_flag, finish_status);
		if (line == NULL)
		{
			line = ft_strdup("exit");
		}
		tokens = lexer(line); // free ok)
		parsed_tokens = parser(&tokens, env_list, finish_status);
		//ここでsyntax error出したい
		if (parsed_tokens == NULL)
		{
			ft_lstclear(&tokens, (void *)free_token);
			ft_lstclear(&parsed_tokens, (void *)free_parsed_token);
			free(line);
			continue ;
		}
		if (check_syntax_error(parsed_tokens, tokens, finish_status) == NG)
		{
			add_history(line);
			ft_lstclear(&tokens, (void *)free_token);
			ft_lstclear(&parsed_tokens, (void *)free_parsed_token);
			free(line);
			continue ;
		}
		pids = malloc(sizeof(int) * ft_lstsize(parsed_tokens));
		pipefds = malloc_pipefds(parsed_tokens);
		tmp = parsed_tokens;
		while (tmp != NULL)
		{
			exec_one_cmd(pids, pipefds, tmp, cmd_index, &env_list,
				finish_status);
			cmd_index++;
			tmp = tmp->next;
			i++;
		}
		wait_for_child_and_store_status(pids, cmd_index, finish_status);
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
