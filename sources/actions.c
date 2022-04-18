/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:50:30 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/18 21:59:04 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_msg(char *str, t_philo *philo)
{
	if (philo->data->one_death == 0 && philo->nbof_eat <= philo->data->max_eat)
		printf("%lld %d %s\n", get_actual_time() - philo->born_time, \
		philo->id, str);
}

int	stop_conditions(t_philo *philo)
{
	if (philo->data->one_death == 1)
		return (1);
	if (philo->data->max_eat > 0 && philo->nbof_eat >= philo->data->max_eat)
	{
		return (1);
	}
	if (get_actual_time() >= philo->last_eat + philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->m_prints);
		printf("%lld %d died\n", get_actual_time() - philo->born_time, \
		philo->id);
		pthread_mutex_unlock(&philo->data->m_prints);
		philo->data->one_death = 1;
		return (1);
	}
	return (0);
}

void	grab_forks_n_eat(t_philo *philo)
{
	if (philo->data->one_death == 0 && philo->nbof_eat <= philo->data->max_eat)
	{
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_lock(&philo->data->m_prints);
		print_msg("has taken a fork", philo);
		pthread_mutex_unlock(&philo->data->m_prints);
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		pthread_mutex_lock(&philo->data->m_prints);
		print_msg("has taken a fork", philo);
		pthread_mutex_unlock(&philo->data->m_prints);
		print_msg("is eating", philo);
		if (philo->data->max_eat != -1)
		{
			philo->nbof_eat++;
			printf("philo %d a eat : [%d] times\n", philo->id, philo->nbof_eat);
		}
		philo->last_eat = get_actual_time();
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	}
}

void	sleep_and_think(t_philo *philo)
{
	if (philo->data->one_death == 0 && philo->nbof_eat <= philo->data->max_eat)
	{
		pthread_mutex_lock(&philo->data->m_prints);
		print_msg("is sleeping", philo);
		pthread_mutex_unlock(&philo->data->m_prints);
		usleep(philo->data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->data->m_prints);
		print_msg("is thinking", philo);
		pthread_mutex_unlock(&philo->data->m_prints);
	}
}

void	*threads_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(2000);
	while (!stop_conditions(philo))
	{
		grab_forks_n_eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
