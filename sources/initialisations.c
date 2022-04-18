#include "../philo.h"


t_data *init_data(char **av, int start)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("malloc() error\n"), NULL);
	data->start_of_program = start;
	data->number_of_philosophers = atl(av[1]);
	data->time_to_die = atl(av[2]);
	data->time_to_eat = atl(av[3]);
	data->time_to_sleep = atl(av[4]);
	data->one_is_dead = 0;
	if (av[5])
		data->max_eat = atl(av[5]);
	else
		data->max_eat = -1;
	return (data);
}

// creer un tab de mutex 
// associer 2 mutex pour chaque philo (droite et gauche)
int 	init_mutex(t_data *data)
{
	int				nbofphilo;

	nbofphilo = data->number_of_philosophers;
	data->forks = malloc(sizeof(pthread_mutex_t) * nbofphilo);
	if (!data->forks)
		return (printf("malloc() error\n"), 0);
	while (nbofphilo--)
		pthread_mutex_init(&data->forks[nbofphilo], NULL);
	pthread_mutex_init(&data->m_prints, NULL);
	return (1);
}

t_philo  *init_philo(t_data *data)
{
	t_philo *philo;
	int i;

	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return (printf("malloc() error\n"), NULL);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		philo[i].data = data;
		philo[i].born_time = get_actual_time();
		philo[i].l_fork = i + 1;
		philo[i].r_fork = i;
		if (i + 1 == data->number_of_philosophers)
			philo[i].l_fork = 0;
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].data = data;
		if (data->max_eat == -1)
			philo[i].number_of_eat = -2;
		else
			philo[i].number_of_eat = 0;
	}
	return (philo);
}

int threads_handler(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, threads_actions, &philo[i]) != 0)
		{
			kill_all(philo);
			return (printf("pthread_create() error\n"), 0);
		}
	}
	// kill_all(philo);
	// on creer 2 loops car avant de terminer les threads avec join,
	// on attends qu'ils soient tous crees
	// pthread_join = similaire a wait() pour les processes,
	// attend que le thread termine avant de continuer le programme
	i = -1;
	while(++i < philo->data->number_of_philosophers)
		pthread_join(philo[i].philo_thread, NULL);
	return (1);
}


void	kill_all(t_philo *philo)
{
	while (--philo->data->number_of_philosophers)
		pthread_mutex_destroy(&philo->data->forks[philo->data->number_of_philosophers]);
	pthread_mutex_destroy(&philo->data->m_prints);
	free(philo->data->forks);
	free(philo->data);
	free(philo);
}