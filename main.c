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

void	eating(t_root *root, int philo_index)
{
	printf("\033[92mphilo[%d] start eating\n\033[0m", philo_index + 1);
	usleep(root->time_to_eat);
	root->philo[philo_index].last_eat = getimes();
	printf("\033[92mphilo[%d] stop eating at [%ld]\n\033[0m", philo_index + 1, getimes());
}

void	sleeping(t_root *root, int philo_index)
{
	printf("\033[93mphilo[%d] sleep...\n\033[0m", philo_index  + 1);
	usleep(root->time_to_sleep);
	printf("\033[93mphilo[%d] stop sleep... [%ld]\n\033[0m",philo_index + 1, getimes());
}

void    *func1(void *arg)
{
	// static int i = 0;
	// t_root root = *(t_root*)arg;
	int index = *(int *)arg;

    
    // pthread_mutex_lock(&mutex);

    // pthread_mutex_unlock(&mutex);
	while (1)
	{
		if (getimes() >= root.start_time + root.time_to_die && root.philo[index].last_eat == 0)
			break ;
		else if (getimes() >= root.philo[index].last_eat + root.time_to_die && root.philo[index].last_eat != 0)
			break;
		printf("pense...\n");
		eating(&root, index);
		sleeping(&root, index);

		// usleep(400);
	}

	i++;
    pthread_exit(NULL);
}

void	*func2(void *arg)
{
	int philo = *(int *)arg;
	printf("philo [%d]\n", philo);
}

void	*func3(void *arg)
{
	t_root root = *(t_root*)arg;
	printf("philo [%d]\n", root.philo[root.index_philo].id);
}

void	*func4(void *arg)
{
	static int i = 1;
	t_root root = *(t_root*)arg;
	printf("philo [%d]\n", i);
	i++;
}

void	init(t_root *root, char **av)
{
	root->number_of_philosophers = atl(av[1]);
	root->time_to_die = atl(av[2]);
	root->time_to_eat = atl(av[3]);
	root->time_to_sleep = atl(av[4]);
	root->index_philo = -1;
}

void print_msg(t_root *root, char *msg)
{
	int i = 0;
	while (i < root->number_of_philosophers)
	{
		printf("philo[%d] %s\n", i, msg);
		i++;
	}
}


int main(int ac, char **av)
{

	// t_root root;
	// int i = -1;
	int ms = 0;
	
	root.start_time = getimes();
	init(&root, av);

	printf("%ld\n", root.start_time);
	printf("%ld\n", root.start_time + root.time_to_die);

	pthread_mutex_init(&mutex, NULL);
	if (ac != 5)
	{
		printf("needs 4 args\n");
		return (EXIT_FAILURE);
	}
	root.philo = malloc(sizeof(t_philo) * root.number_of_philosophers);
	if (!root.philo)
		return (EXIT_FAILURE);

	while(++root.index_philo < root.number_of_philosophers)
	{
		root.philo[root.index_philo].id = root.index_philo + 1;
		root.philo[root.index_philo].last_eat = 0;
		if (pthread_create(&root.philo[root.index_philo].philo_thread, NULL, func1, (void *)&root.philo[root.index_philo].id) != 0)
		{
			printf("thread_create() error\n");
			return (EXIT_FAILURE);
		}
		printf("Philo %ld is alive at [%ld]\n", root.philo[root.index_philo].id, getimes());

	}
	// on creer 2 loops car avant de terminer les threads avec join, on attends qu'ils soient tous crees
	root.index_philo = -1;
	while(++root.index_philo  < root.number_of_philosophers)
	{
		// similaire a wait() pour les processes, attend que le thread termine avant de continuer le programme
		pthread_join(root.philo[root.index_philo ].philo_thread, NULL);
		printf("Philo %ld died at [%ld]\n", root.philo[root.index_philo ].id, getimes());
	}

	// // while (1)
	// // {
	// // 	printf("\n%d ms\n", ms);
	// // 	if (ms == root.time_to_die)
	// // 	{
	// // 		print_msg(&root, "vient de mourir");
	// // 		break;
	// // 	}
	// // 	if (ms == 0)
	// // 		print_msg(&root, "nait");
	// // 	ms+=200;
	// // }
	// // printf("%ld\n", root.philo[0]->id);
	// // free(root.philo[0]);
	// // printf("%ld\n", root.philo[0]->id);

	// pthread_mutex_destroy(&mutex);
	return (0);
}