/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:28:06 by atokamot          #+#    #+#             */
/*   Updated: 2023/08/25 10:11:48 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = ft_calloc(s1_len + s2_len + 1, 1);
	if (result == NULL)
		return (NULL);
	ft_strlcat(result, (char *)s1, s1_len + 1);
	ft_strlcat(result, (char *)s2, s1_len + s2_len + 1);
	return (result);
}

/*
int	main(void)
{
	printf("%s\n", ft_strjoin("hello", "world"));
}
*/
