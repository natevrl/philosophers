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
	int			number_of_eat;
	pthread_t	philo_thread;
	
	struct s_data *data;

} t_philo;

typedef struct s_data
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_eat;
	int start_of_program;
	pthread_mutex_t *forks;
	t_philo *philos;

} t_data;

// utils
long long	atl(char *nptr);
long long	get_actual_time(void);
int			ft_strlen(char *str);
void	ft_usleep(int ms);

// actions
void	*threads_actions(void *arg);
void	t_grab_forks(t_philo *philo);
void	t_eat(t_philo *philo);
void	t_sleep(t_philo *philo);

// init & destory
t_data	*init_data(char **av, int start);
int 	init_mutex(t_data *data);
// int 	init_philo(t_data *data);
t_philo  *init_philo(t_data *data);
int threads_handler(t_philo *philo);
void	kill_all(t_philo *philo);

// parsing
int		error_handling(int ac, char **av);
