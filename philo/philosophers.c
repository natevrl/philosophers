/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhado <nbenhado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 21:34:26 by nbenhado          #+#    #+#             */
/*   Updated: 2022/01/20 18:43:57 by nbenhado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void    *func1(void *arg)
{
    int i = -1;
    char str[] = "111 jsuis le thread 111";
    
    (void)arg;
    pthread_mutex_lock(&mutex);
    while (str[++i])
    {
        printf("\033[93m%c\033[0m\n", str[i]);
        usleep(300);
    }
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
        printf("\033[93m%c\033[0m\n", str[i]);
        usleep(300);
    }
    pthread_mutex_unlock(&mutex);
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