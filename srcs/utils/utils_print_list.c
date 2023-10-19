#include "libft.h"
#include "main.h"

void	print_env(t_env *env)
{
	printf("name: [%s] ", (char *)env->name);
	printf("value: [%s]\n", (char *)env->value);
}

void	print_token(t_token *token)
{
	printf("	content: [%s] ", (char *)token->token_content);
	if (token->status == TK_NORMAL)
		printf("status: [NORMAL]\n");
	if (token->status == TK_GREATER_THAN)
		printf("status: [GREATER_THAN]\n");
	if (token->status == TK_LESS_THAN)
		printf("status: [LESS_THAN]\n");
	if (token->status == TK_PIPE)
		printf("status: [PIPE]\n");
	if (token->status == TK_SPACE)
		printf("status: [SPACE]\n");
	if (token->status == TK_SINGLE_QUOTE)
		printf("status: [SINGLE_QUOTE]\n");
	if (token->status == TK_DOUBLE_QUOTE)
		printf("status: [DOUBLE_QUOTE]\n");
	if (token->status == TK_DOLL)
		printf("status: [DOLL]\n");
	if (token->status == TK_USED)
		printf("status: [USED]\n");
	//
	if (token->status == RD_ERROR)
		printf("status: [RD_ERROR]\n");
	if (token->status == RD_IN)
		printf("status: [RD_IN]\n");
	if (token->status == RD_OUT)
		printf("status: [RD_OUT]\n");
	if (token->status == RD_HEAEDOC)
		printf("status: [RD_HEAEDOC]\n");
	if (token->status == RD_APPEND)
		printf("status: [RD_APPEND]\n");
}

void	print_parsed_token(t_parsed_token *parsed_token)
{
	printf("------print_parsed_token------\n");
	printf("redirect:\n");
	ft_lstiter(parsed_token->redirect, (void *)print_token);
	printf("     cmd:\n");
	ft_lstiter(parsed_token->cmd, (void *)print_token);
	printf("    args:\n");
	ft_lstiter(parsed_token->args, (void *)print_token);
}