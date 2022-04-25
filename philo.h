/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:41:39 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/25 14:42:35 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	long long		last_eat;
	int				l_fork;
	int				r_fork;
	int				nbof_eat;
	pthread_t		philo_thread;	
	struct s_data	*data;

}	t_philo;

typedef struct s_data
{
	int					nbof_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat;
	long long			start_of_program;
	int					one_death;
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_prints;
	pthread_mutex_t		m_death;
	pthread_mutex_t		m_eat;
	t_philo				*philos;

}	t_data;

// utils
long long	atl(char *nptr);
long long	current_time(void);
int			ft_strlen(char *str);
void		print_msg(char *str, t_philo *philo);
int			check_max_eat(t_philo *philo);

// actions
int			not_dead(t_data *data);
int	stop_conditions(t_philo *philo);
void		*threads_act(void *arg);
int			grab_forks_n_eat(t_philo *philo);
void		t_eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);

// init & destory
t_data		*init_data(char **av, long long start);
int			init_mutex(t_data *data);
t_philo		*init_philo(t_data *data);
int			threads_handler(t_philo *philo);
void		kill_all(t_philo *philo);

// parsing
int			error_handling(int ac, char **av);

#endif
