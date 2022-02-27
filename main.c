/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:42:13 by ubuntu            #+#    #+#             */
/*   Updated: 2022/02/27 22:34:17 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;

static long long atl(char *nptr)
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

long long	getimes(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 10000) + (t.tv_usec / 10000));
}

void	eating(t_philo *philo)
{
	long long before_eating;
	// pthread_mutex_lock(&mutex);
	before_eating = getimes();
	printf("\033[92mphilo[%d] start eating at [%lli]\n\033[0m", philo->id, before_eating - philo->born_time);
	usleep(philo->data->time_to_eat);
	philo->last_eat = getimes();
	printf("\033[92mphilo[%d] stop eating at [%lli]\n\033[0m", philo->id, philo->last_eat - philo->born_time);
	// pthread_mutex_unlock(&mutex);

}

void	sleeping(t_philo *philo)
{
	printf("\033[93mphilo[%d] sleep...\n\033[0m", philo->id);
	usleep(philo->data->time_to_sleep);
	printf("\033[93mphilo[%d] stop sleep... [%lli]\n\033[0m", philo->id, getimes() - philo->born_time);
}

void *func1(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	// pthread_mutex_lock(&mutex);
	// pthread_mutex_unlock(&mutex);
	while (1)
	{
		if (getimes() >= philo->born_time + philo->data->time_to_die && philo->last_eat == 0)
		{

			printf("----CA RENTRE----\n");
			break;
		}
		else if (getimes() >= philo->last_eat + philo->data->time_to_die && philo->last_eat != 0)
		{
			printf("----CA RENTRE----\n");
			break;
		}
		// usleep(150000);
		printf("[%d] : pense...\n", philo->id);
		eating(philo);
		sleeping(philo);
	}
	pthread_exit(NULL);
}

t_data *init_data(t_data *data, char **av, int start)
{
	data = malloc(sizeof(t_data));
	data->start_of_program = start;
	data->number_of_philosophers = atl(av[1]);
	data->time_to_die = atl(av[2]);
	data->time_to_eat = atl(av[3]);
	data->time_to_sleep = atl(av[4]);
	return (data);
}

void print_msg(t_data *data, char *msg)
{
	int i = 0;
	while (i < data->number_of_philosophers)
	{
		printf("philo[%d] %s\n", i, msg);
		i++;
	}
}

int main(int ac, char **av)
{

	long long start_of_program = getimes();
	t_philo *philo;
	int i;
	int ms = 0;

	if (ac != 5)
	{
		printf("needs 4 args\n");
		return (-1);
	}

	philo = malloc(sizeof(t_philo) * atl(av[1]));
	if (!philo)
		return (-1);
	// pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < atl(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].born_time = getimes();
		philo[i].data = init_data(philo[i].data, av, start_of_program);

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
		printf("Philo %d died at [%lli]\n", philo[i].id, getimes());
	}

	// // while (1)
	// // {
	// // 	printf("\n%d ms\n", ms);
	// // 	if (ms == data.time_to_die)
	// // 	{
	// // 		print_msg(&data, "vient de mourir");
	// // 		break;
	// // 	}
	// // 	if (ms == 0)
	// // 		print_msg(&data, "nait");
	// // 	ms+=200;
	// // }
	// // printf("%ld\n", data.philo[0]->id);
	// // free(data.philo[0]);
	// // printf("%ld\n", data.philo[0]->id);

	// pthread_mutex_destroy(&mutex);
	return (0);
}