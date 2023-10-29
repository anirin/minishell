/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_to_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:42:35 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 20:22:45 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"

char	**envlist_to_envp(t_list *env_list)
{
	t_env	*env;
	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		tmp = ft_strjoin(env->name, "=");
		ret[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env_list = env_list->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
