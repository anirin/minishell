#include "libft.h"
#include "main.h"

//コマンドを受けて返すだけのshell
int	minishell(void)
{
	t_list	*tokens;
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("$> ");
		if (strncmp("exit", line, 4) == 0)
		{
			printf("bye!\n");
			exit(0);
		}
		tokens = lexer(line);
		print_list(tokens);
		add_history(line);
		free(line);
	}
	return (0);
}

int	main(void)
{
	minishell();
}