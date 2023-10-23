#include "builtins.h"
#include "libft.h"
#include "main.h"

char	**parse_env(char *token) // ok
{
	char **parsed_env;
	char *tmp;
	int count;
	int i;

	i = 0;
	count = 0;
	parsed_env = ft_calloc(4, sizeof(char *));
	parsed_env[3] = NULL;
	while (token[i] != '\0')
	{
		if (strncmp(&token[i], "+=", 2) == 0 && count != 0)
		{
			parsed_env[0] = ft_substr(token, 0, count);
			parsed_env[1] = ft_strdup("+=");
			if (token[i + 2] != '\0')
			{
				tmp = ft_strdup(&token[i + 2]);
				tmp = ft_strtrim(tmp, "\""); //ここはシビや
				// free
				parsed_env[2] = tmp;
			}
			else
				parsed_env[2] = ft_strdup("");
			return (parsed_env);
		}
		else if (strncmp(&token[i], "=", 1) == 0 && count != 0)
		{
			parsed_env[0] = ft_substr(token, 0, count);
			parsed_env[1] = ft_strdup("=");
			if (token[i + 1] != '\0')
				parsed_env[2] = ft_strdup(&token[i + 1]);
			else
				parsed_env[2] = ft_strdup("");
			return (parsed_env);
		}
		count++;
		i++;
	}
	parsed_env[0] = ft_strdup(token);
	parsed_env[1] = NULL;
	parsed_env[2] = NULL;
	return (parsed_env);
}

t_list	*envp_convert_to_envlist(char **envp) // ok
{
	int i;
	t_list *env_list;
	t_env *env;
	t_list *new;
	char **parsed_env;

	i = 0;
	env_list = NULL;
	while (envp[i] != NULL)
	{
		env = malloc(sizeof(t_env));
		parsed_env = parse_env(envp[i]);
		env->name = ft_strdup(parsed_env[0]);
		env->value = ft_strdup(parsed_env[2]);
		new = ft_lstnew(env);
		ft_lstadd_back(&env_list, new);
		free(parsed_env[0]);
		free(parsed_env[1]);
		free(parsed_env[2]);
		free(parsed_env);
		i++;
	}
	return (env_list);
}

int	is_added_env(char *env_name, t_list *env_list) // ok
{
	int count;
	t_env *env;

	count = 0;
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (ft_strncmp(env->name, env_name, ft_strlen(env->name) + 1) == 0)
			return (count);
		env_list = env_list->next;
		count++;
	}
	return (-1);
}

void	append_env(int env_index, char *env_content, t_list *env_list) // ok
{
	char *tmp;
	t_env *env;

	while (env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	env = (t_env *)env_list->content;
	tmp = env->value;
	env->value = ft_strjoin(tmp, env_content);
	free(tmp);
}

void	overwrite_env(int env_index, char *env_value, t_list *env_list) // ok
{
	t_env *env;

	while (env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	env = (t_env *)env_list->content;
	free(env->value);
	env->value = ft_strdup(env_value);
}

void	add_env(char **parsed_env, t_list **env_list)
{
	char *new_env_value;
	t_list *new_lst;
	t_env *new_env;

	if (ft_strncmp(parsed_env[0], "=", 1) == 0)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(parsed_env[0], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_finish_status = 1;
		return ;
	}
	new_env = malloc(sizeof(t_env));
	if (parsed_env[1] != NULL)
		new_env_value = ft_strdup(parsed_env[2]);
	else
		new_env_value = NULL; //ここは」かなり注意
	new_env->name = ft_strdup(parsed_env[0]);
	new_env->value = new_env_value;
	new_lst = ft_lstnew(new_env);
	ft_lstadd_back(env_list, new_lst);
	// freeしろ
}

void	print_export(void *env_list)
{
	t_env *env;

	env = (t_env *)env_list;
	printf("declare -x %s=\"%s\"\n", env->name, env->value);
}

bool	check_export_error(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 0 || ft_isdigit(str[0]) != 0)
		{
			printf("export: not valid in this context:");
			printf("%s\n", str);
			g_finish_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}

void	my_export(t_list **env_list, t_list *args) // export TEST =CC エラー処理
{
	int env_index;
	char **parsed_env;

	env_index = 0;
	if (args == NULL)
	{
		ft_lstiter(*env_list, (void *)print_export);
		return ;
	}
	while (args != NULL)
	{
		parsed_env = parse_env(((t_token *)args->content)->token_content);
		if (check_export_error(parsed_env[0]) == false)
			break;
		env_index = is_added_env(parsed_env[0], *env_list);
		if (env_index != -1)
		{
			if (parsed_env[1] != NULL && ft_strncmp(parsed_env[1], "+=", 3) == 0)
				append_env(env_index, parsed_env[2], *env_list);
			if (parsed_env[1] != NULL && ft_strncmp(parsed_env[1], "=", 2) == 0)
				overwrite_env(env_index, parsed_env[2], *env_list);
		}
		else
			add_env(parsed_env, env_list);
		free_array(parsed_env);
		args = args->next;
	}
}