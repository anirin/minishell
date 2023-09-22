#include "libft.h"
#include "main.h"

void print_env(t_env *env)
{
	printf("--------------------\n");
	printf("env_name: [%s]\n", env->env_name);
	printf("env_value: [%s]\n", env->env_value);
}

void print_token(t_token *token)
{
	printf("--------------------\n");
	printf("content: [%s] ", token->token_content);
	printf("status: [%d]\n", token->status);
}

void print_parsed_token(t_parsed_token *parsed_token)
{
	printf("--------------------\n");
	printf("greater_than:");
	ft_lstiter(parsed_token->greater_than, (void *)print_token);
	printf("less_than:");
	ft_lstiter(parsed_token->less_than, (void *)print_token);
	printf("cmd:");
	ft_lstiter(parsed_token->cmd, (void *)print_token);
}