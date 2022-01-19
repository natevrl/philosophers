/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:34:26 by nbenhado          #+#    #+#             */
/*   Updated: 2022/01/19 22:12:11 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void    *func1(void *arg)
{
    int i = -1;

    (void)arg;
    while (++i < 10)
    {
        printf("\033[96mthread 1: %d\033[0m\n", i);
        usleep(300);
    }
    pthread_exit(NULL);
}

void    *func2(void *arg)
{
    int i = -1;

    (void)arg;
    while (++i < 10)
    {
        printf("\033[93mthread 2: %d\033[0m\n", i);
        usleep(300);
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t   thread1;
    pthread_t   thread2;

    pthread_create(&thread1, NULL, func1, NULL);
    pthread_create(&thread2, NULL, func2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // usleep(1000);
    return (0);
}