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

void    *func1(void *arg)
{
    int i = -1;
	static int y = 0;
    char str[] = "jsuis le thread :";
	t_root root = *(t_root*)arg;
    
    pthread_mutex_lock(&mutex);
    while (str[++i])
    {
		if (root.philo[y]->id == 1)
        	printf("\033[93m%c\033[0m", str[i]);
		else if (root.philo[y]->id == 2)
    	    printf("\033[92m%c\033[0m", str[i]);
		else if (root.philo[y]->id == 3)
        	printf("\033[94m%c\033[0m", str[i]);
		else        	
			printf("\033[95m%c\033[0m", str[i]);
        usleep(300);
    }
    pthread_mutex_unlock(&mutex);
	printf(" %d\n", root.philo[y]->id);
	y++;

    pthread_exit(NULL);
}


void	init(t_root *root, char **av)
{
	root->number_of_philosophers = atl(av[1]);
	root->time_to_die = atl(av[2]);
	root->time_to_eat = atl(av[3]);
	root->time_to_sleep = atl(av[4]);
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

	t_root root;
	int i = -1;
	int ms = 0;
	pthread_mutex_init(&mutex, NULL);

	if (ac != 5)
	{
		printf("needs 4 args\n");
		return (-1);
	}

	init(&root, av);

	root.philo = malloc(sizeof(t_philo) * root.number_of_philosophers);
	if (!root.philo)
		return (EXIT_FAILURE);

	while(++i < root.number_of_philosophers)
	{
		root.philo[i] = malloc(sizeof(t_philo));
		if (!root.philo)
			return (-1);
		root.philo[i]->id = i + 1;
		// printf("%d\n", root.philo[i]->id);
		if (pthread_create(&root.philo[i]->philo_thread, NULL, func1, &root) != 0)
		{
			printf("thread_create() error\n");
			return (EXIT_FAILURE);
		}
		printf("Thread %d has started\n", i + 1);
		// similaire a wait() pour les processes, attend que le thread termine avant de continuer le programme

	}
	// on creer 2 loops car avant de terminer les threads avec join, on attends qu'ils soient tous crees
	i = -1;
	while(++i < root.number_of_philosophers)
	{
		pthread_join(root.philo[i]->philo_thread, NULL);
		printf("Thread %d has finished\n", i + 1);
	}

	// while (1)
	// {
	// 	printf("\n%d ms\n", ms);
	// 	if (ms == root.time_to_die)
	// 	{
	// 		print_msg(&root, "vient de mourir");
	// 		break;
	// 	}
	// 	if (ms == 0)
	// 		print_msg(&root, "nait");
	// 	ms+=200;
	// }
	// printf("%ld\n", root.philo[0]->id);
	// free(root.philo[0]);
	// printf("%ld\n", root.philo[0]->id);

	pthread_mutex_destroy(&mutex);
	return (0);
}