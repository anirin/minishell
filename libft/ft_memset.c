/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:46:10 by atokamot          #+#    #+#             */
/*   Updated: 2023/08/25 10:11:48 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = buf;
	i = 0;
	while (i < n)
	{
		*p++ = (unsigned char)ch;
		i++;
	}
	return (buf);
}
