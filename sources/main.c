/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Crt_eated: 2022/02/27 17:42:13 by ubuntu            #+#    #+#             */
/*   Updated: 2022/03/06 22:34:38 by v3r              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int main(int ac, char **av)
{
	long long start_of_program = get_actual_time();
	t_data *data;
	t_philo *philo;

	if (!error_handling(ac, av))
		return (-1);
	data = init_data(av, start_of_program);
	if (!init_mutex(data))
		return (-1);
	philo = init_philo(data);
	data->philos = philo;
	// printf("test\n");
	threads_handler(philo);
	kill_all(philo);
	return (0);
}