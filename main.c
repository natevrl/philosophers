#include "philo.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
    static int y = 1;
    char str[] = "jsuis le thread :";
    
    (void)arg;
    pthread_mutex_lock(&mutex);
    while (str[++i])
    {
        printf("\033[93m%c\033[0m", str[i]);
        usleep(300);
    }
    printf(" %d\n", y++);
    pthread_mutex_unlock(&mutex);
    // pthread_exit(NULL);
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
	int i = 0;
	int ms = 0;

	if (ac != 5)
	{
		printf("needs 4 args\n");
		return (-1);
	}

	init(&root, av);

	root.philo = malloc(sizeof(t_philo) * root.number_of_philosophers);
	if (!root.philo)
		return (-1);
		root.philo->philo_thread = malloc(sizeof(pthread_t) * root.number_of_philosophers);
	if (!root.philo->philo_thread)
		return (-1);
	root.philo->id = malloc(sizeof(int) * root.number_of_philosophers);
	if (!root.philo->id)
		return (-1);


	while(i < root.number_of_philosophers)
	{
		root.philo->id[i] = i;
		// printf("%d\n", root.philo->id[i]);
		pthread_create(&root.philo->philo_thread[i], NULL, func1, NULL);
    	// pthread_join(root.philo->philo_thread[i], NULL);
		// printf("%ld\n", root.philo->philo_thread[i]);
		i++;
	}
	while (1)
	{
		printf("%d ms\n", ms);
		if (ms == root.time_to_die)
		{
			print_msg(&root, "vient de mourir");
			break;
		}
		if (ms == 0)
			print_msg(&root, "nait");
		ms+=200;
	}

	return (0);
}