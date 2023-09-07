#include "libft.h"
#include "main.h"

int	 	**count_and_exec_pipe(t_list *tokens)
{
	int **pipefds;
	int pipe_num;
	int i;
	t_list *tmp;

	pipe_num = 0;
	i = 0;
	tmp = tokens;
	while (tokens != NULL)
	{
		// printf("content = [%s]\n", tokens->content);
		// printf("ft_strncmp = [%d]\n", ft_strncmp(tokens->content, "|", 1));
		// printf("status = [%d]\n", tokens->status);
		if (tokens->status == SPECIAL && ft_strncmp(tokens->content, "|", 1) == 0)
			pipe_num++;
		tokens = tokens->next;
	}
	pipefds = ft_calloc(sizeof(int *), pipe_num + 1);
	{
		while (i < pipe_num)
		{
			pipefds[i] = ft_calloc(sizeof(int), 2);
			i++;
		}
	}
	pipefds[i] = NULL;
	// printf("pipe num = %d, pipefds[0] = %p\n", pipe_num, pipefds[0]);
	return (pipefds);
}



void	redirect_pipe_stdio(int **pipefds, int exec_num)
{
	// printf("exec_num %d, pipefds[0] %p\n", exec_num, pipefds[0]);
	if (pipefds[0] == NULL)
		return ;
	if (exec_num == 0)
	{
		dup2(pipefds[exec_num][1], STDOUT_FILENO);
		close(pipefds[exec_num][0]);
	}
	else
	{
		dup2(pipefds[exec_num - 1][0], STDIN_FILENO);
		close(pipefds[exec_num - 1][1]);
		if (pipefds[exec_num] != NULL)
		{
			dup2(pipefds[exec_num][1], STDOUT_FILENO);
			close(pipefds[exec_num][0]);
		}
	}
}

void	redirect_stdout(t_list *head)
{
	int fd;

	while(head != NULL && (!(head->status == SPECIAL && ft_strncmp(head->content, "|", 1) == 0)))
	{
		if (head->status == SPECIAL && ft_strncmp(head->content, ">", 1) == 0)
		{
			head = head->next;
			fd = open(head->content, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
			// printf("out changed fd = %d\n", fd);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		head = head->next;
	}
}

void	redirect_stdin(t_list *head)
{
	int fd;

	while(head != NULL && (!(head->status == SPECIAL && ft_strncmp(head->content, "|", 1) == 0)))
	{
		if (head->status == SPECIAL && ft_strncmp(head->content, "<", 1) == 0)
		{
			head = head->next;
			fd = open(head->content, O_RDONLY);
			// printf("in changed fd = %d\n", fd);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		head = head->next;
	}
}

int		count_cmd(t_list *head)
{
	int i;

	i = 0;
	//pipe が見つかるまで進める
	while(head != NULL && (!(head->status == SPECIAL && ft_strncmp(head->content, "|", 1) != 0)))
	{
		if ((head->status == SPECIAL && ft_strncmp(head->content, ">", 1) == 0) 
			|| (head->status == SPECIAL && ft_strncmp(head->content, "<", 1) == 0))
			head = head->next->next;
		else
		{
			i++;
			head = head->next;
		}
	}
	return (i);
}

char	**set_cmd(t_list *head)
{
	char **cmd;
	int i;
	int cmd_word_num;

	cmd_word_num = count_cmd(head);	
	cmd = ft_calloc(sizeof(char *), cmd_word_num + 1);
	i = 0;
	while(head != NULL && (!(head->status == SPECIAL && ft_strncmp(head->content, "|", 2) == 0)))
	{
		if ((head->status == SPECIAL && ft_strncmp(head->content, ">", 1) == 0) 
			|| (head->status == SPECIAL && ft_strncmp(head->content, "<", 1) == 0))
			head = head->next->next;
		else
		{
			cmd[i] = ft_strdup(head->content);
			head = head->next;
			i++;
		}
	}
	cmd[i] = NULL;
	return (cmd);
}

void	move_head(t_list **head)
{
	while(*head != NULL)
	{
		if ((*head)->status == SPECIAL && ft_strncmp((*head)->content, "|", 1) == 0)
		{
			*head = (*head)->next;
			break;
		}
		*head = (*head)->next;
	}
}

void close_for_last_two_pipefds(int **pipefds, int exec_num)
{
	int count;

	count = 0;
	while (exec_num - 2 >= 0 && count < 2)
	{
		close(pipefds[exec_num - 2][0]);
		close(pipefds[exec_num - 2][1]);
		exec_num--;
		count++;
	}
}

void free_pipefds(int **pipefds, int exec_num)
{
	int i;

	i = 0;
	while (i < exec_num)
	{
		free(pipefds[i]);
		i++;
	}
	free(pipefds);
}

void wait_for_last_two_exec(int *pid, int exec_num, int sataus)
{
	int count;

	count = 0;
	while (exec_num - 1 >= 0 && count < 2)
	{
		waitpid(pid[exec_num - 1], &sataus, 0);
		exec_num--;
		count++;
	}
}

char *get_path(char *cmd)
{
	char *path;
	char *tmp;
	char **path_arr;
	int i;

	i = 0;
	path = getenv("PATH"); //ここの変更が必要! 環境変数の変更後に対応できない
	path_arr = ft_split(path, ':');
	if (access(cmd, F_OK) == 0)
	{
		return (cmd);
	}
	while(path_arr[i] != NULL)
	{
		tmp = ft_strjoin(path_arr[i], "/");
		path_arr[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path_arr[i], F_OK) == 0)
			break;
		i++;
	}
	return (path_arr[i]);
}