/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:42:02 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/19 19:08:56 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	*init_data(char **av, int start)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("malloc() error\n"), NULL);
	data->start_of_program = start;
	data->nbof_philos = atl(av[1]);
	data->time_to_die = atl(av[2]);
	data->time_to_eat = atl(av[3]);
	data->time_to_sleep = atl(av[4]);
	data->one_death = 0;
	if (av[5])
		data->max_eat = atl(av[5]);
	else
		data->max_eat = -1;
	return (data);
}

// creer un tab de mutex 
// associer 2 mutex pour chaque philo (droite et gauche)
int	init_mutex(t_data *data)
{
	int				nbofphilo;

	nbofphilo = data->nbof_philos;
	data->forks = malloc(sizeof(pthread_mutex_t) * nbofphilo);
	if (!data->forks)
		return (printf("malloc() error\n"), 0);
	while (nbofphilo--)
		pthread_mutex_init(&data->forks[nbofphilo], NULL);
	pthread_mutex_init(&data->m_prints, NULL);
	pthread_mutex_init(&data->m_death, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	return (1);
}

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->nbof_philos);
	if (!philo)
		return (printf("malloc() error\n"), NULL);
	i = -1;
	while (++i < data->nbof_philos)
	{
		philo[i].data = data;
		philo[i].born_time = get_actual_time();
		philo[i].l_fork = i + 1;
		philo[i].r_fork = i;
		// if (data->nbof_philos != 1)
		// 	philo[i].r_fork = i;
		// else
		// 	philo[i].r_fork = -1;
		if (i + 1 == data->nbof_philos)
			philo[i].l_fork = 0;
		philo[i].id = i + 1;
		philo[i].last_eat = philo[i].born_time;
		philo[i].data = data;
		if (data->max_eat == -1)
			philo[i].nbof_eat = -2;
		else
			philo[i].nbof_eat = 0;
	}
	return (philo);
}

// on creer 2 loops car avant de terminer les threads avec join,
// on attends qu'ils soient tous crees
// pthread_join = similaire a wait() pour les processes,
// attend que le thread termine avant de continuer le programme
int	threads_handler(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->nbof_philos)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, threads_act, \
		&philo[i]) != 0)
		{
			kill_all(philo);
			return (printf("pthread_create() error\n"), 0);
		}
	}
	i = -1;
	while (++i < philo->data->nbof_philos)
	{
		if (pthread_join(philo[i].philo_thread, NULL) != 0)
		{
			kill_all(philo);
			return (printf("pthread_join() error\n"), 0);
		}
	}
	return (1);
}

void	kill_all(t_philo *philo)
{
	while (--philo->data->nbof_philos)
		pthread_mutex_destroy(&philo->data->forks[philo->data->nbof_philos]);
	pthread_mutex_destroy(&philo->data->m_prints);
	pthread_mutex_destroy(&philo->data->m_death);
	pthread_mutex_destroy(&philo->data->m_eat);
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}
