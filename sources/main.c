/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:48:38 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/18 21:49:21 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	long long	start_of_program;
	t_data		*data;
	t_philo		*philo;

	start_of_program = get_actual_time();
	if (!error_handling(ac, av))
		return (-1);
	data = init_data(av, start_of_program);
	if (!init_mutex(data))
		return (-1);
	philo = init_philo(data);
	data->philos = philo;
	threads_handler(philo);
	kill_all(philo);
	return (0);
}
