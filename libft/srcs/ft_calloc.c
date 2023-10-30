/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:20:42 by atokamot          #+#    #+#             */
/*   Updated: 2023/09/30 09:13:40 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ret;

	if (size != 0 && num > SIZE_MAX / size)
		return (NULL);
	ret = malloc(num * size);
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, 0, num * size);
	return (ret);
}

/*
int	main(void)
{
	//printf("origin=%p\n", calloc(SIZE_MAX, SIZE_MAX));
	//printf("origin=%p\n", calloc(LONG_MAX, 1));
	printf("origin=%p\n", calloc(ULONG_MAX, 1));
	printf("origin=%p\n", calloc(SIZE_MAX, 1));
}
*/
