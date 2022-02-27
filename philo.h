#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// typedef struct s_root;

typedef struct s_philo
{
	int id;
	long long last_eat;
	long long born_time;
	pthread_t philo_thread;
	struct s_data *data;

} t_philo;

typedef struct s_data
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int start_of_program;
} t_data;

// t_root root;
