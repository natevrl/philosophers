/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:49:33 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/19 18:59:13 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"



int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	atl(char *nptr)
{
	int			i;
	int			negatif;
	long long	result;

	i = 0;
	result = 0;
	negatif = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) | (nptr[i] == ' '))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			negatif = -1;
		i++;
	}
	i -= 1;
	while (nptr[++i] >= '0' && nptr[i] <= '9')
		result = result * 10 + nptr[i] - '0';
	result *= negatif;
	return (result);
}

long long	get_actual_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (printf("gettimeofday() failed"), 0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
