#include "philo.h"

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;

static long long	atl(char *nptr)
{
	int			i;
	int			negatif;
	long long	result;

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

long long getimes()
{
	struct timeval start;
	// unsigned long int micro_second;

	gettimeofday(&start, NULL);
	return (start.tv_usec);
}

// void	eating(t_data *data, int philo_index)
// {
// 	printf("\033[92mphilo[%d] start eating\n\033[0m", philo_index + 1);
// 	usleep(data->time_to_eat);
// 	data->philo[philo_index].last_eat = getimes();
// 	printf("\033[92mphilo[%d] stop eating at [%lld]\n\033[0m", philo_index + 1, getimes());
// }

// void	sleeping(t_data *data, int philo_index)
// {
// 	printf("\033[93mphilo[%d] sleep...\n\033[0m", philo_index  + 1);
// 	usleep(data->time_to_sleep);
// 	printf("\033[93mphilo[%d] stop sleep... [%lld]\n\033[0m",philo_index + 1, getimes());
// }

void    *func1(void *arg)
{
	// static int i = 0;
	t_philo *philo = (t_philo *)arg;
	
	// philo->data->time_to_die;
	printf("TTTT= %lld\n", philo->data->start_time);
	exit(0);
    // pthread_mutex_lock(&mutex);
	
    // pthread_mutex_unlock(&mutex);
	printf("----CA RENTRE----\n");
	while (1)
	{
		if (getimes() >= (*philo).data->start_time + (*philo).data->time_to_die && (*philo).last_eat == 0)
			break ;
		else if (getimes() >=  (*philo).last_eat + (*philo).data->time_to_die && (*philo).last_eat != 0)
			break;

		printf("pense...\n");
		// eating((*philo).data, (*philo).id);
		// sleeping((*philo).data, (*philo).id);

		// usleep(400);
	}
    pthread_exit(NULL);
}

void	*func2(void *arg)
{
	int philo = *(int *)arg;
	printf("philo [%d]", philo);
}

// void	*func3(void *arg)
// {
// 	t_data data = *(t_data*)arg;
// 	printf("philo [%d]\n", data.philo[data.index_philo].id);
// }

// void	*func4(void *arg)
// {
// 	static int i = 1;
// 	t_data data = *(t_data*)arg;
// 	printf("philo [%d]\n", i);
// 	i++;
// }

t_data	*init_data(t_data *data, char **av)
{
	data = malloc(sizeof(t_data));
	data->start_time = getimes();
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

	t_philo *philo;
	int i = -1;
	int ms = 0;
	
	philo = malloc(sizeof(t_philo) * atl(av[1]));
	if (!philo)
		return (-1);

	// printf("%lld\n", data.start_time);
	// printf("%lld\n", data.start_time + data.time_to_die);
	pthread_mutex_init(&mutex, NULL);
	if (ac != 5)
	{
		printf("needs 4 args\n");
		return (-1);
	}
	while(++i < atl(av[1]))
	{
		philo[i].id = i + 1;
		printf("%d\n", philo[i].id);
		philo[i].last_eat = 0;
		philo[i].data = init_data(philo[i].data, av);

		if (pthread_create(&philo[i].philo_thread, NULL, func1, &philo[i]) != 0)
		{
			printf("thread_create() error\n");
			return (-1);
		}
		printf("Philo %d is alive at [%lld]\n", philo[i].id, getimes());

	}
	return 0;
	// on creer 2 loops car avant de terminer les threads avec join, 
	// on attends qu'ils soient tous crees
	// i = -1;
	// while(++i < data.number_of_philosophers)
	// {
	// 	// similaire a wait() pour les processes, 
	// 	// attend que le thread termine avant de continuer le programme
	// 	pthread_join(data.philo[i].philo_thread, NULL);
	// 	printf("Philo %d died at [%lld]\n", data.philo[i].id, getimes());
	// }

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