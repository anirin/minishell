/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lstnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:51:48 by atsu              #+#    #+#             */
/*   Updated: 2023/09/12 15:59:50 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

t_env_list	*env_lstnew(char *env_name, char *env_value)
{
	t_env_list	*p;

	p = malloc(sizeof(t_env_list));
	if (p == NULL)
		return (NULL);
	p->env_name = env_name;
	p->env_value = env_value;
	p->next = NULL;
	return (p);
}