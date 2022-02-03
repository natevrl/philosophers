#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo
{
	int id;
	long long last_eat;
	pthread_t philo_thread;

} t_philo;

typedef struct s_root
{
	int number_of_philosophers;
	long long start_time;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int index_philo;
	t_philo	*philo;
} t_root;

t_root root;
