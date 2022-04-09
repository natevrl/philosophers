#include "../philo.h"

void	t_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	printf("%lld %d has taken a fork\n", get_actual_time() - philo->born_time, philo->id);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	printf("%lld %d has taken a fork\n", get_actual_time() - philo->born_time, philo->id);
}

void	t_eat(t_philo *philo)
{
	printf("%lld %d is eating\n", get_actual_time() - philo->born_time, philo->id);
	philo->number_of_eat++;
	philo->last_eat = get_actual_time();
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
}

void	t_sleep(t_philo *philo)
{
	printf("\033[1;94m%lli %d is sleeping\n\033[0m", get_actual_time() - philo->born_time, philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

int stop_conditions(t_philo *philo)
{
	if (philo->data->max_eat > 0)
	{
		printf("philo %d a eat : [%d] times\n", philo->id, philo->number_of_eat);
		if ( (get_actual_time() >= philo->born_time + philo->data->time_to_die && philo->last_eat == 0)
			|| (get_actual_time() >= philo->last_eat + philo->data->time_to_die 
				&& philo->last_eat > 0) || (philo->number_of_eat > philo->data->max_eat) )
				return (1);
	}
	else
	{
		printf("CARENTR\n");
		if ((get_actual_time() >= philo->born_time + philo->data->time_to_die && philo->last_eat == 0) 
			|| (get_actual_time() >= philo->last_eat + philo->data->time_to_die && philo->last_eat > 0))
			return (1);
	}
	return (0);
}
void *threads_actions(void *arg)
{
	t_philo *philo; 
	
	philo = (t_philo *)arg;
	while (!stop_conditions(philo))
	{
		t_grab_forks(philo);
		t_eat(philo);
		t_sleep(philo);
		printf("%lld %d is thinking\n", get_actual_time() - philo->born_time, philo->id);
	}
	printf("%lli %d died\n", get_actual_time() - philo->born_time, philo->id);
	kill_all(philo->data->philos);
	pthread_exit(NULL);
}
