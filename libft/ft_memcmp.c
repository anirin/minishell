/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:45:52 by atokamot          #+#    #+#             */
/*   Updated: 2023/08/25 10:11:48 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = buf1;
	p2 = buf2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
