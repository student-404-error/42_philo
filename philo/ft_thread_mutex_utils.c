/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_mutex_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:09:27 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/25 18:27:07 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void ft_destroy_mutex(int num_of_philo, pthread_mutex_t *forks)
{
	for (int i = 0; i < num_of_philo; i++)
		pthread_mutex_destroy(&forks[i]);
}

void ft_free_thread_mutex(int num, t_philo *philo, pthread_mutex_t *forks)
{
	for (int i = 0; i < num; i++)
		pthread_mutex_destroy(&philo[i].state_mutex);
	// destroy forks
	ft_destroy_mutex(num, forks);
	// destroy arg mutexes
	pthread_mutex_destroy(&philo[0].arg->print);
	pthread_mutex_destroy(&philo[0].arg->finish_mutex);
	free(forks);
	free(philo);
}