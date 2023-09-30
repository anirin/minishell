/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:36:40 by atokamot          #+#    #+#             */
/*   Updated: 2023/09/30 09:13:40 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	l;
	unsigned int	i;
	char			*r;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	r = malloc(l + 1);
	if (r == NULL)
		return (NULL);
	while (i < l)
	{
		r[i] = (*f)(i, s[i]);
		i++;
	}
	r[i] = 0;
	return (r);
}
