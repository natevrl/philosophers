/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmv3r <vmv3r@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:49:33 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/25 23:22:42 by vmv3r            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_max_eat(t_philo *philo)
{
	philo->nbof_eat++;
	if (philo->nbof_eat >= philo->data->max_eat)
		return (pthread_mutex_unlock(&philo->data->forks[philo->l_fork]), \
				pthread_mutex_unlock(&philo->data->forks[philo->r_fork]), \
				0);
	return (1);
}

void	print_msg(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_prints);
	if (!stop_conditions(philo))
	{
		printf("%lld %d %s\n", current_time() - philo->data->start_of_program, \
		philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->m_prints);
}

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

long long	current_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (printf("gettimeofday() failed"), -1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
