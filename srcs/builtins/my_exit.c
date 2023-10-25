#include "builtins.h"
#include "libft.h"
#include "main.h"

static int	get_min_result(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result < LONG_MIN / 10)
			return (NG);
		if (result * 10 < LONG_MIN + str[i] - '0')
			return (NG);
		result = result * 10 - str[i] + '0';
		i++;
	}
	return (OK);
}

static long	get_max_result(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > LONG_MAX / 10)
			return (NG);
		if (result * 10 > LONG_MAX - str[i] + '0')
			return (NG);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (OK);
}

static int	is_under_long_max(char *str)
{
	int		sign;
	int		i;
	long	result;

	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (sign == 1)
		return (get_max_result(&str[i]));
	else
		return (get_min_result(&str[i]));
}

static int	is_numeric(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (NG);
		i++;
		count++;
	}
	if (count == 0)
		return (NG);
	return (OK);
}

void	my_exit(t_list *env_list, t_list *cmd, t_list *args, int *finish_status)
{
	t_token *exit_status_token;
	int exit_status;
	char *exit_status_str;
	t_list *tmp;

	(void)env_list;
	tmp = ft_lstlast(cmd);      //後でfreeするために一時的に保持しておかないと都合が悪い
	ft_lstadd_back(&cmd, args); //-e とかも考慮するから
	if (cmd->next == NULL)
	{
		tmp->next = NULL;
		printf("exit\n");
		exit(0);
	}
	exit_status_token = (t_token *)cmd->next->content;
	exit_status_str = (char *)exit_status_token->token_content;
	if (cmd->next->next != NULL && is_numeric(exit_status_str) == OK)
	{
		tmp->next = NULL;
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		*finish_status = 1;
		return ;
	}
	printf("exit\n");
	exit_status = ft_atoi((char *)exit_status_token->token_content);
	tmp->next = NULL;
	if (is_under_long_max(exit_status_str) == OK
		&& is_numeric(exit_status_str) == OK)
	{
		exit_status = exit_status % 256; // minusも同様
		exit(exit_status); // Long max < の場合はnumeric でexitする それまでは255 ~ 0で判定している
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n",
			(char *)exit_status_token->token_content);
		exit(255);
	}
}