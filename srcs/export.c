#include "main.h"
#include "libft.h"

char **parse_env(char *token)
{
	char **parsed_env;
	char *tmp;
	int count;
	int i;

	i = 0;
	count = 0;
	parsed_env = ft_calloc(3, sizeof(char *));
	while(token[i] != '\0')
	{
		if (strncmp(&token[i], "+=", 2) == 0 && count != 0)
		{
			parsed_env[0] = ft_substr(token, 0, count);
			parsed_env[1] = ft_strdup("+=");
			if (token[i + 2] != '\0')
			{
				tmp = ft_strdup(&token[i + 2]);
				tmp = ft_strtrim(tmp, "\""); //ここはシビや
				//free
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

t_env_list	*envp_convert_to_envlist(char **envp)
{
	int i;
	t_env_list *env_list;
	char **parsed_env;

	i = 0;
	env_list = NULL;
	while(envp[i] != NULL)
	{
		parsed_env = parse_env(envp[i]);
		env_lstadd_back(&env_list, env_lstnew(parsed_env[0], parsed_env[2]));
		i++;
	}
	return (env_list);
}

int is_added_env(char *env_name, t_env_list *env_list)
{
	int		count;

	count = 0;
	while(env_list != NULL)
	{
		if (ft_strncmp(env_list->env_name, env_name, ft_strlen(env_list->env_name)) == 0)
			return (count);
		env_list = env_list->next;
		count++;
	}
	return (0);
}

void append_env(int env_index, char *env_content, t_env_list *env_list)
{
	char *tmp;

	printf("append_env\n");
	while(env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	tmp = env_list->env_value;
	env_list->env_value = ft_strjoin(tmp, env_content);
	free(tmp);
}

void overwrite_env(int env_index, char *env_value, t_env_list *env_list)
{
	printf("overwrite_env\n");
	while(env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	free(env_list->env_value);
	env_list->env_value = NULL;
	env_list->env_value = ft_strdup(env_value);
}

void add_env(char **parsed_env, t_env_list **env_list)
{
	printf("add_env\n");
	char *new_env_name;
	char *new_env_value;
	t_env_list *new_lst;

	new_env_name = ft_strdup(parsed_env[0]);
	if (parsed_env[1] != NULL)
		new_env_value = ft_strdup(parsed_env[2]);
	else
		new_env_value = NULL;//ここは」かなり注意
	new_lst = env_lstnew(new_env_name, new_env_value);
	env_lstadd_back(env_list, new_lst);
	//freeしろ
}

void export(t_env_list **env_list, char **cmd)
{
	int i;
	int env_index;
	char **parsed_env;


	env_index = 0;
	i = 1; //cmd[0]はexportなので飛ばす
	while(cmd[i] != NULL)
	{
		parsed_env = parse_env(cmd[i]);
		env_index = is_added_env(parsed_env[0], *env_list);
		printf("env_index = %d\n", env_index);
		if (env_index != 0) //既存環境変数
		{
			if (parsed_env[1] != NULL && strncmp(parsed_env[1], "+=", 3) == 0)
				append_env(env_index, parsed_env[2], *env_list);
			if (parsed_env[1] != NULL && strncmp(parsed_env[1], "=", 2) == 0)
				overwrite_env(env_index, parsed_env[2], *env_list);
		}
		else //新規環境変数
		{
			add_env(parsed_env, env_list);
		}
		i++;
	}
	//ここは消す
	if (cmd[1] == NULL)
		print_env_list(*env_list);
}