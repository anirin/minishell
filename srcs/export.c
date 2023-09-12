#include "main.h"
#include "libft.h"

t_list	*envp_convert_to_linearlist(char **envp)
{
	int i;
	t_list *env_list;
	t_list *parsed_env;

	i = 0;
	env_list = NULL;
	while(envp[i] != NULL)
	{
		parsed_env = parse_env(envp[i]);
		ft_lstadd_back(&env_list, ft_lstnew(envp[i]));
		i++;
	}
	return (env_list);
}

int is_added_env(char *cmd, t_list *env_list)
{
	t_list *tmp;
	int		count;
	char	*env_plus_equal;

	count = 0;
	tmp = env_list;
	env_plus_equal = ft_strjoin(cmd, "=");
	while(tmp != NULL)
	{
		// printf("cmd:%s\n", cmd);
		// printf("tmp->content:%s\n", tmp->content);
		if (ft_strncmp(cmd, tmp->content, ft_strlen(cmd)) == 0)
			return (count);
		tmp = tmp->next;
		count++;
	}
	return (0);
}

t_list *parse_env(char *cmd)
{
	t_list *cmd_list;
	int count;
	int i;

	i = 0;
	cmd_list = NULL;
	count = 0;
	while(cmd[i] != '\0')
	{
		if (strncmp(&cmd[i], "+=", 2) == 0 && count != 0)
		{
			ft_lstadd_back(&cmd_list, ft_lstnew(ft_substr(cmd, 0, count)));
			//例外処理してない
			ft_lstadd_back(&cmd_list, ft_lstnew(ft_strdup("+=")));
			if (cmd[i + 1] != '\0')
				ft_lstadd_back(&cmd_list, ft_lstnew(ft_strdup(&cmd[i + 1])));
			else
				ft_lstadd_back(&cmd_list, ft_lstnew(ft_strdup("")));
			return (cmd_list);
		}
		else if (strncmp(&cmd[i], "=", 1) == 0 && count != 0)
		{
			ft_lstadd_back(&cmd_list, ft_lstnew(ft_substr(cmd, 0, count)));
			//例外処理してない aa= 的なやつを
			// printf("count:%d\n", count);
			ft_lstadd_back(&cmd_list, ft_lstnew(ft_strdup("=")));
			if (cmd[i + 1] != '\0')
				ft_lstadd_back(&cmd_list, ft_lstnew(ft_strdup(&cmd[i + 1])));
			else
				ft_lstadd_back(&cmd_list, ft_lstnew(ft_strdup("")));
			return (cmd_list);
		}
		count++;
		i++;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(ft_strdup(cmd)));
	return (cmd_list);
}

void append_env(int env_index, char *env_content, t_list *env_list)
{
	char *tmp;

	printf("append_env\n");
	while(env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	tmp = env_list->content;
	printf("tmp:%s\n", (char *)tmp);
	printf("env_content:%s\n", (char *)env_content);
	env_list->content = ft_strjoin(tmp, env_content);
	// free(tmp);
}

void overwrite_env(int env_index, char *env, t_list *env_list)
{
	printf("overwrite_env\n");
	while(env_index != 0)
	{
		env_list = env_list->next;
		env_index--;
	}
	free(env_list->content);
	env_list->content = NULL;
	env_list->content = ft_strdup(env);
}

void add_env(t_list *parsed_cmd, t_list **env_list)
{
	char *new_env;
	t_list *new_lst;

	new_env = ft_strdup(parsed_cmd->content);
	if (parsed_cmd->next == NULL)
	{
		new_lst = ft_lstnew(new_env);
		ft_lstadd_back(env_list, new_lst);
		return ;
	}
	new_env = ft_strjoin(new_env, "=");
	new_env = ft_strjoin(new_env, parsed_cmd->next->next->content);
	new_lst = ft_lstnew(new_env);
	ft_lstadd_back(env_list, new_lst);
	//freeしろ
}

void export(t_list **env_list, char **cmd)
{
	int i;
	int env_index;
	t_list *parsed_env;


	env_index = 0;
	i = 1; //cmd[0]はexportなので飛ばす
	while(cmd[i] != NULL)
	{
		parsed_env = parse_cmd(cmd[i]);
		env_index = is_added_env(parsed_env->content, *env_list);
		printf("env_index:%d\n", env_index);
		if (env_index != 0) //既存環境変数
		{
			if (strncmp(parsed_env->next->content, "+=", 2) == 0)
				append_env(env_index, parsed_env->next->next->content, *env_list);
			if (strncmp(parsed_env->next->content, "=", 1) == 0)
				overwrite_env(env_index, cmd[i], *env_list);
		}
		else //新規環境変数
		{
			add_env(parsed_env, env_list);
		}
		i++;
		ft_lstclear(&parsed_env, free);
	}
	//ここは消す
	if (cmd[1] == NULL)
		print_list(*env_list);
}