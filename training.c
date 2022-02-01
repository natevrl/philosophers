/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v3r <v3r@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:34:26 by nbenhado          #+#    #+#             */
/*   Updated: 2022/02/01 15:33:10 by v3r              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

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
    pthread_exit(NULL);
}

void    *func2(void *arg)
{
    int i = -1;
    char str[] = "222 jsuis le thread 222";
    
    (void)arg;
    pthread_mutex_lock(&mutex);
    while (str[++i])
    {
        printf("\033[96m%c\033[0m", str[i]);
        usleep(3000);
    }
    pthread_mutex_unlock(&mutex);
    printf("\n");
    pthread_exit(NULL);
}

int main(int ac, char **av)
{
    pthread_t   *thread;
	int i = 0;


    (void)ac;
	thread = malloc(sizeof(pthread_t) * atl(av[1]));
	if (!thread)
		return (-1);

	while(i < atl(av[1]))
	{
		pthread_create(&thread[i], NULL, func1, NULL);
		// printf("%ld\n", thread[i]);
    	// pthread_join(thread[i], NULL);
		i++;
	}

    // thread = malloc(sizeof(pthread_t) * atl(av[1]));
    // if (!thread)
	// 	return (-1);
    // pthread_create(&thread[0], NULL, func1, NULL);
    // pthread_create(&thread[1], NULL, func1, NULL);
    // pthread_join(thread[0], NULL);
    // pthread_join(thread[1], NULL);
    // printf("%ld\n", thread[0]);
    // printf("%ld", thread[1]);
    return (0);
}