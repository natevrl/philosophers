/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:42:13 by ubuntu            #+#    #+#             */
/*   Updated: 2022/03/06 22:12:24 by v3r              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//FAIRE LE PARSING (int overflow etc..)
// GERER LES DATAS RACE


void	eating(t_philo *philo)
{
	// pthread_mutex_lock(&mutex);
	printf("\033[1;92m%lli %d is eating\n\033[0m", getimes() - philo->born_time, philo->id);
	philo->last_eat = getimes();
	usleep(philo->data->time_to_eat * 1000);
	// printf("\033[1;92m%lli %d is eating\n\033[0m", philo->id, philo->last_eat);
	// pthread_mutex_unlock(&mutex);

}

void	sleeping(t_philo *philo)
{
	printf("\033[1;94m%lli %d is sleeping\n\033[0m", getimes() - philo->born_time, philo->id);
	usleep(philo->data->time_to_sleep * 1000);
	// printf("\033[1;94m%lli %d is sleeping\n\033[0m", philo->id, getimes() - philo->born_time);
}

void *func1(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
		if (getimes() >= philo->born_time + philo->data->time_to_die && philo->last_eat == 0)
		{

			printf("----CA RENTRE----\n");
			break;
		}
		else if (getimes() >= philo->last_eat + philo->data->time_to_die && philo->last_eat > 0)
		{
			printf("----CA RENTRE----\n");
			break;
		}
		printf("%lld %d is thinking\n", getimes() - philo->born_time, philo->id);
		// pthread_mutex_lock(&philo->data->mutex);
		eating(philo);
		// pthread_mutex_unlock(&philo->data->mutex);
		sleeping(philo);
	}
	pthread_exit(NULL);
}

t_data *init_data(char **av, int start)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	data->start_of_program = start;
	data->number_of_philosophers = atl(av[1]);
	data->time_to_die = atl(av[2]);
	data->time_to_eat = atl(av[3]);
	data->time_to_sleep = atl(av[4]);
	return (data);
}



int main(int ac, char **av)
{

	long long start_of_program = getimes();
	t_philo *philo;
	int i;
	t_data *data = init_data(av, start_of_program);
	

	if (ac != 5)
	{
		printf("Invalid params : ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
		return (-1);
	}

	philo = malloc(sizeof(t_philo) * atl(av[1]));
	if (!philo)
		return (-1);
	i = -1;
	// init_forks(philo[i]);
	while (++i < atl(av[1]))
	{
		philo[i].born_time = getimes();
		philo[i].l_fork = i + 1;
		philo[i].r_fork = i;
		if (i + 1 == atl(av[1]))
			philo[i].l_fork = 0;
		// printf("philo[%d]:::::: R = %d || L = %d\n", i, philo[i].r_fork, philo[i].l_fork);
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].data = data;
		// pthread_mutex_init(&philo[i].data->mutex, NULL);

		if (pthread_create(&philo[i].philo_thread, NULL, func1, &philo[i]) != 0)
		{
			printf("thread_create() error\n");
			return (-1);
		}
		printf("Philo %d is alive at [time = %lli]\n", philo[i].id, philo[i].born_time);
	}
	
	// on creer 2 loops car avant de terminer les threads avec join,
	// on attends qu'ils soient tous crees
	i = -1;
	while(++i <  philo[0].data->number_of_philosophers)
	{
		// similaire a wait() pour les processes,
		// attend que le thread termine avant de continuer le programme
		pthread_join(philo[i].philo_thread, NULL);
		printf("%lli %d  id dead\n", getimes(), philo[i].id);
	}

	// pthread_mutex_destroy(&mutex);
	return (0);
}