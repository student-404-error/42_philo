/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:28:15 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/25 16:23:09 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "philo.h"

pthread_mutex_t	mtx;

void	*thread_body(void *arg)
{
	int	*shared_var_ptr = (int *) arg;

	// 임계 구역 잠금( 뮤텍스 잠금 )
	pthread_mutex_lock(&mtx);
	(*shared_var_ptr) += 1;
	printf("%d\n", *shared_var_ptr);
	pthread_mutex_unlock(&mtx);
	// 임계 구역 해제 ( 뮤텍스 해제 )
	return (NULL);
}

void	*thread_body2(void *arg)
{
	int	*shared_var_ptr = (int *) arg;

	// 임계 구역 잠금
	pthread_mutex_lock(&mtx);
	(*shared_var_ptr) += 2;
	printf("%d\n", *shared_var_ptr);
	pthread_mutex_unlock(&mtx);
	// 임계 구역 해제
	return (NULL);
}

int	main(int ac, char *av[])
{
	(void) av;
	(void) ac;
	int	shared_var = 0;

	struct timeval tv;
	time_t	current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec;
	if (ac != 5 && ac != 6)
		printf("%d %d %d\n", tv.tv_hour, );

	// thread 핸들러
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_mutex_init(&mtx, NULL);
	
	int	result1 = pthread_create(&thread1, NULL, thread_body, &shared_var);
	int	result2 = pthread_create(&thread2, NULL, thread_body2, &shared_var);

	if (result1 || result2)
	{
		printf("Thread could not be created.\n");
		exit(1);
	}
	result1 = pthread_join(thread1, NULL);
	result2 = pthread_join(thread2, NULL);
	if (result1 || result2)
	{
		printf("The thread could not be detached.\n");
		exit(2);
	}
	
	result = pthread_join(thread, NULL);
	if (result)
	{
		printf("The thread could not be joined. Error number: %d\n", result);
		exit(2);
	}
	pthread_mutex_destroy(&mtx);
	return (0);
}*/
