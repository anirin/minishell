/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:27:06 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 10:27:22 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "builtins.h"

void	my_env(t_list *env_list, t_list *cmd, t_list *args)
{
	t_env	*env;

	(void)cmd;
	(void)args;
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (env->value != NULL)
			printf("%s=%s\n", (char *)env->name, (char *)env->value);
		env_list = env_list->next;
	}
}
