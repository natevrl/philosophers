/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:59:11 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/28 13:29:56 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// check if : 
// --------> Enough args
// --------> args are valid numbers
// --------> args are digit
// --------> no int overflow
// --------> no empty args ""
int	error_handling(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (printf("5 or 6 args needed\n"), 0);
	while (--ac)
	{
		if (av[ac][0] == '\0' || av[ac][0] == '0')
			return (printf("Empty arg(s) or 0 spotted\n"), 0);
		if (atl(av[ac]) > 2147483647 || atl(av[ac]) < -2147483648 \
		|| ft_strlen(av[ac]) > 12)
			return (printf("Please retry with valid int\n"), 0);
		i = -1;
		while (av[ac][++i])
			if (av[ac][i] < '0' || av[ac][i] > '9')
				return (printf("Non-digit arg(s) spotted"), 0);
	}
	return (1);
}
