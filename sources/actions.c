/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmv3r <vmv3r@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:50:30 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/25 23:09:39 by vmv3r            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	not_dead(t_data *data)
{
	pthread_mutex_lock(&data->m_death);
	if (data->one_death == 1)
		return (pthread_mutex_unlock(&(data->m_death)), 0);
	return (pthread_mutex_unlock(&data->m_death), 1);
}

int	stop_conditions(t_philo *philo)
{
	if (!not_dead(philo->data))
		return (1);
	if (philo->data->max_eat > 0 && philo->nbof_eat >= philo->data->max_eat)
		return (1);
	if (current_time() > philo->last_eat + philo->data->time_to_die)
	{
		printf("%lld %d died\n", current_time() - philo->data->start_of_program, \
		philo->id);
		pthread_mutex_lock(&philo->data->m_death);
		philo->data->one_death = 1;
		pthread_mutex_unlock(&philo->data->m_death);
		return (1);
	}
	return (0);
}

// if (philo->id != philo->data->nbof_philos)
	// pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
// else
	// pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
// print_msg("has taken a fork", philo);
// if (philo->id != philo->data->nbof_philos)
	// pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
// else
	// pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
int	grab_forks_n_eat(t_philo *philo)
{
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		print_msg("has taken a fork", philo);
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		print_msg("has taken a fork", philo);
		print_msg("is eating", philo);
		if (philo->data->max_eat != -1)
		{
			if (!check_max_eat(philo))
				return (0);
		}
		philo->last_eat = current_time();
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	return (1);
}

void	sleep_and_think(t_philo *philo)
{
		print_msg("is sleeping", philo);
		usleep(philo->data->time_to_sleep * 1000);
		print_msg("is thinking", philo);
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
			if (current_time() >= philo->last_eat + philo->data->time_to_die)
				return (print_msg("died", philo), NULL);
	}
	if (philo->id % 2 != 0)
		usleep(19000);
	while (1)
	{
		if (grab_forks_n_eat(philo))
			sleep_and_think(philo);
		if (stop_conditions(philo))
			break;
	}
	return (NULL);
}
