#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// typedef struct s_root;

typedef struct s_philo
{
	int			id;
	long long	last_eat;
	long long	born_time;
	int			l_fork;
	int			r_fork;
	pthread_t	philo_thread;
	
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
	pthread_mutex_t mutex;

} t_data;

long long atl(char *nptr);
long long	getimes(void);

