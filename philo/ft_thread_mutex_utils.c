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

void	ft_join_thread(int num_of_philo, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	ft_destroy_mutex(int num_of_philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}

void	ft_free_thread_mutex(int num, t_philo *philo, pthread_mutex_t *fork)
{
	ft_destroy_mutex(num, fork);
	free(fork);
	free(philo);
}
