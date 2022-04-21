/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:48:38 by nbenhado          #+#    #+#             */
/*   Updated: 2022/04/21 20:19:01 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	long long	start_of_program;
	t_data		*data;

	start_of_program = get_actual_time();
	if (!error_handling(ac, av))
		return (-1);
	data = init_data(av, start_of_program);
	data->philos = init_philo(data);
	if (!init_mutex(data) || !data->philos || !data)
		return (kill_all(data->philos), -1);
	threads_handler(data->philos);
	kill_all(data->philos);
	return (0);
}
