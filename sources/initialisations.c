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
	data->time_to_t_eat = atl(av[3]);
	data->time_to_t_sleep = atl(av[4]);

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
	return (1);
}

int  init_philo(t_data *data)
{
	t_philo *philo;
	int i;

	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return (printf("malloc() error\n"), 0);
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		philo[i].born_time = get_actual_time();
		philo[i].l_fork = i + 1;
		philo[i].r_fork = i;
		if (i + 1 == data->number_of_philosophers)
			philo[i].l_fork = 0;
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].data = data;
		if (pthread_create(&philo[i].philo_thread, NULL, threads_handler, &philo[i]) != 0)
			return (printf("pthread_create() error\n"), 0);

	}

	i = -1;
	// on creer 2 loops car avant de terminer les threads avec join,
	// on attends qu'ils soient tous crees
	while(++i < data->number_of_philosophers)
	{
		// similaire a wait() pour les processes,
		// attend que le thread termine avant de continuer le programme
		pthread_join(philo[i].philo_thread, NULL);
		printf("%lli EXIT", get_actual_time() - philo[i].born_time);
	}
	return (1);
}