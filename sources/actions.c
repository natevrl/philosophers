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
	// philo->total_nbr_of_meals += 1;
	philo->last_eat = get_actual_time();
	usleep(philo->data->time_to_t_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
}

void	t_sleep(t_philo *philo)
{
	printf("\033[1;94m%lli %d is sleeping\n\033[0m", get_actual_time() - philo->born_time, philo->id);
	usleep(philo->data->time_to_t_sleep * 1000);
}

void *threads_handler(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
		if (get_actual_time() >= philo->born_time + philo->data->time_to_die && philo->last_eat == 0)
		{
			printf("%lli %d died\n", get_actual_time() - philo->born_time, philo->id);
			exit(-1);
            break ;
		}
		else if (get_actual_time() >= philo->last_eat + philo->data->time_to_die && philo->last_eat > 0)
		{
			printf("%lli %d died\n", get_actual_time() - philo->born_time, philo->id);
			exit(-1);
            break ;
		}
		t_grab_forks(philo);
		t_eat(philo);
		t_sleep(philo);
		printf("%lld %d is thinking\n", get_actual_time() - philo->born_time, philo->id);
	}
	pthread_exit(NULL);
}
