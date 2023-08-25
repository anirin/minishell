/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atsu <atsu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:31:22 by atokamot          #+#    #+#             */
/*   Updated: 2023/08/25 10:11:48 by atsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	get_len(int n)
{
	long	tmp;
	size_t	count;

	tmp = n;
	count = 1;
	if (n < 0)
	{
		count++;
		tmp *= -1;
	}
	while (tmp > 9)
	{
		tmp /= 10;
		count++;
	}
	return (count);
}

static void	get_str(int n, int len, char *result)
{
	long	tmp;

	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		result[0] = '-';
	}
	result[len--] = 0;
	if (n == 0)
		result[len] = '0';
	while (tmp > 0)
	{
		result[len--] = (tmp % 10) + '0';
		tmp /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;

	len = get_len(n);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	get_str(n, len, result);
	return (result);
}
