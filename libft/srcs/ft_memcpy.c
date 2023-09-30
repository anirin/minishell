/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:46:01 by atokamot          #+#    #+#             */
/*   Updated: 2023/09/30 09:13:40 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;

	if (buf1 == NULL && buf2 == NULL)
		return (NULL);
	p1 = (unsigned char *)buf1;
	p2 = (unsigned char *)buf2;
	while (n--)
		*p1++ = *p2++;
	return ((void *)buf1);
}

/*
int	main(void)
{
	char	buf[];

	buf[] = "test";
	printf("%s\n", memcpy(buf, NULL, 4));
}
*/
