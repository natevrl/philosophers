/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Crt_eated: 2022/03/06 21:33:06 by v3r               #+#    #+#             */
/*   Updated: 2022/03/06 21:48:16 by v3r              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// void print_msg(t_data *data, char *msg)
// {
// 	int i = 0;
// 	while (i < data->number_of_philosophers)
// 	{
// 		printf("philo[%d] %s\n", i, msg);
// 		i++;
// 	}
// }

long long atl(char *nptr)
{
	int i;
	int negatif;
	long long result;

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

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}