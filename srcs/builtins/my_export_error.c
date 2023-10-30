/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atokamot <atokamot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:26:08 by atokamot          #+#    #+#             */
/*   Updated: 2023/10/29 10:26:29 by atokamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "main.h"

bool	check_export_error(char *str, int *finish_status)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 0 || ft_isdigit(str[0]) != 0)
		{
			printf("export: not valid in this context:");
			printf("%s\n", str);
			*finish_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}
