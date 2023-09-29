#include "libft.h"
#include "main.h"


void	free_token(t_token *token)
{
	free(token->token_content);
}

void	free_env(t_env *env)
{
	free(env->env_name);
	free(env->env_value);
}

void	free_parsed_token(t_parsed_token *parsed_token)
{
	ft_lstclear(&parsed_token->greater_than, (void *)free_token);
	ft_lstclear(&parsed_token->less_than, (void *)free_token);
	ft_lstclear(&parsed_token->cmd, (void *)free_token);
	ft_lstclear(&parsed_token->args, (void *)free_token);
}