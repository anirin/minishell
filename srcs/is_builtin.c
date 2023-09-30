#include "main.h"
#include "libft.h"

int		is_builtin(t_list *cmd_and_option)
{
	t_token *token_cmd;
	char *str;

	if (cmd_and_option == NULL)
		return (BT_NOTBUILTIN);
	token_cmd = (t_token *)cmd_and_option->content;
	str = token_cmd->token_content;
	if (ft_strncmp(str, "export", 7) == 0)
		return (BT_EXPORT);
	// if (ft_strncmp(str, "echo", 5) == 0)
	// 	return (BT_ECHO);
	// if (ft_strncmp(str, "cd", 3) == 0)
	// 	return (BT_CD);
	// if (ft_strncmp(str, "pwd", 4) == 0)
	// 	return (BT_PWD);
	// if (ft_strncmp(str, "unset", 6) == 0)
	// 	return (BT_UNSET);
	// if (ft_strncmp(str, "env", 4) == 0)
	// 	return (BT_ENV);
	// if (ft_strncmp(str, "exit", 5) == 0)
	// 	return (BT_EXIT);
	return (BT_NOTBUILTIN);
}