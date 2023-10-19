#include "libft.h"
#include "main.h"

void	free_token(t_token *token)
{
	free(token->token_content);
	free(token);
}

void	free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
}

void	free_parsed_token(t_parsed_token *parsed_token)
{
	ft_lstclear(&parsed_token->redirect, (void *)free_token);
	ft_lstclear(&parsed_token->cmd, (void *)free_token);
	ft_lstclear(&parsed_token->args, (void *)free_token);
	free(parsed_token);
}