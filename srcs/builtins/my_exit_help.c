/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:44:27 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 10:36:34 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

static int	get_min_result(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result < LONG_MIN / 10)
			return (NG);
		if (result * 10 < LONG_MIN + str[i] - '0')
			return (NG);
		result = result * 10 - str[i] + '0';
		i++;
	}
	return (OK);
}

static long	get_max_result(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > LONG_MAX / 10)
			return (NG);
		if (result * 10 > LONG_MAX - str[i] + '0')
			return (NG);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (OK);
}

int	is_under_long_max(char *str)
{
	int		sign;
	int		i;
	long	result;

	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (sign == 1)
		return (get_max_result(&str[i]));
	else
		return (get_min_result(&str[i]));
}

int	is_numeric(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (NG);
		i++;
		count++;
	}
	if (count == 0)
		return (NG);
	return (OK);
}
