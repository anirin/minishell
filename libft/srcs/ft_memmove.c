/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:46:04 by atokamot          #+#    #+#             */
/*   Updated: 2023/09/30 09:13:40 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *buf1, const void *buf2, size_t n)
{
	unsigned char		*p1;
	const unsigned char	*p2;

	if (buf1 == NULL && buf2 == NULL)
		return (NULL);
	p1 = buf1;
	p2 = buf2;
	if (buf1 <= buf2)
	{
		while (n--)
			*p1++ = *p2++;
	}
	else
	{
		p1 += n - 1;
		p2 += n - 1;
		while (n--)
			*p1-- = *p2--;
	}
	return (buf1);
}
