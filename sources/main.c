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

// FAIRE LE PARSING (int overflow etc..)
// GERER LES DATAS RACE
// PROTEGER TOUT LES APPELS SYSTEMES
// KILL_ALL (mutex, threads, malloc...)

int main(int ac, char **av)
{

	long long start_of_program = get_actual_time();
	t_data *data;
	
	if (!error_handling(ac, av))
		return (-1);
	data = init_data(av, start_of_program);
	if (!init_mutex(data))
		return (-1);
	init_philo(data);
	
	// pthread_mutex_destroy(&mutex);
	return (0);
}