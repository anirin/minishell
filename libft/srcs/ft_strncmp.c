/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:14:10 by atokamot          #+#    #+#             */
/*   Updated: 2023/09/30 09:13:40 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if ((s1 == NULL || s2 == NULL) && n == 0)
		return (0);
	while (s1[i] != 0 && s2[i] != 0 && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

/*
int	main(void)
{
	char	*str;
	char	*cmp2;
	int		len;

	str = "libft-test-tokyo";
	cmp2 = calloc(10, 1);
	len = strlen(str);
	printf("origin=%d\n", strncmp("hello", NULL, 0));
	printf("ft=%d, origin=%d\n" ,strncmp(NULL, "hello", 0), strncmp(NULL,
				"hello", 0));
	printf("ft=%d, origin=%d\n" ,strncmp(NULL, NULL, 0), strncmp(NULL, NULL,
				0));
}
*/