/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:50:30 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/19 23:06:52 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int     not_dead(t_data *data)
{
        pthread_mutex_lock(&data->m_death);
        if (data->one_death == 1)
                return (pthread_mutex_unlock(&(data->m_death)), 0);
        return (pthread_mutex_unlock(&data->m_death), 1);
}

void	print_msg(char *str, t_philo *philo)
{
	// if (philo->data->one_death == 0 && philo->nbof_eat <= philo->data->max_eat)
	if (not_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->m_prints);
		printf("%lld %d %s\n", get_actual_time() - philo->born_time, \
		philo->id, str);
		pthread_mutex_unlock(&philo->data->m_prints);
	}
}

int	stop_conditions(t_philo *philo)
{
	if ((philo->data->one_death == 1)|| (philo->data->max_eat > 0 && philo->nbof_eat >= philo->data->max_eat))
		return (1);
	if (get_actual_time() >= philo->last_eat + philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->m_prints);
		printf("%lld %d died\n", get_actual_time() - philo->born_time, \
		philo->id);
		pthread_mutex_unlock(&philo->data->m_prints);
        pthread_mutex_lock(&philo->data->m_death);
		philo->data->one_death = 1;
        pthread_mutex_unlock(&philo->data->m_death);
		return (1);
	}
	return (0);
}

void	grab_forks_n_eat(t_philo *philo)
{
	if (not_dead(philo->data))
	{
		if (philo->id != philo->data->nbof_philos)
			pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		else
			pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		print_msg("has taken a fork", philo);
		if (philo->id != philo->data->nbof_philos)
			pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		else
			pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		print_msg("has taken a fork", philo);
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
	if (not_dead(philo->data))
	{
		print_msg("is sleeping", philo);
		usleep(philo->data->time_to_sleep * 1000);
		print_msg("is thinking", philo);
	}
}

void	*threads_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->r_fork == -1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		print_msg("has taken a fork", philo);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		while (1)
			if (get_actual_time() >= philo->last_eat + philo->data->time_to_die)
				return (print_msg("died", philo), NULL);
	}
	if (philo->id % 2 == 0)
		usleep(200000);
	while (!stop_conditions(philo))
	{
		grab_forks_n_eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
