/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:58:11 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/25 18:22:02 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int ft_init_fork(t_arg *arg, pthread_mutex_t **forks)
{
	int i;

	*forks = malloc(sizeof(pthread_mutex_t) * arg->num_of_philo);
	if (!*forks)
		return (MALLOC_ERR);
	for (i = 0; i < arg->num_of_philo; i++)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
		{
			for (int j = 0; j < i; j++)
				pthread_mutex_destroy(&(*forks)[j]);
			free(*forks);
			return (PTHREAD_ERR);
		}
	}
	return (SUCCESS);
}

int ft_init_arg(t_arg *arg, int ac, char **av)
{
	if (pthread_mutex_init(&arg->print, NULL) != 0)
		return (PTHREAD_ERR);
	if (pthread_mutex_init(&arg->finish_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&arg->print);
		return (PTHREAD_ERR);
	}
	arg->num_of_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->must_eat_count = (ac == 6) ? ft_atoi(av[5]) : 0;
	arg->start_time = ft_get_ms();
	arg->finish = 0;
	arg->finished_eat = 0;
	if (arg->num_of_philo <= 0 || arg->time_to_die <= 0 || arg->time_to_eat <= 0 || arg->time_to_sleep <= 0 || (ac == 6 && arg->must_eat_count <= 0))
		return (ARG_ERR);
	return (SUCCESS);
}

int ft_init_philo(t_arg *arg, t_philo **philo, pthread_mutex_t *forks)
{
	int i;
	int j;

	*philo = malloc(sizeof(t_philo) * arg->num_of_philo);
	if (!*philo)
		return (MALLOC_ERR);
	i = 0;
	while (i < arg->num_of_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].eat_count = 0;
		(*philo)[i].arg = arg;
		(*philo)[i].left_fork = &forks[i];
		(*philo)[i].right_fork = &forks[(i + 1) % arg->num_of_philo];
		if (pthread_mutex_init(&(*philo)[i].state_mutex, NULL) != 0)
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&(*philo)[j++].state_mutex);
			return (free(*philo), PTHREAD_ERR);
		}
		i++;
	}
	return (SUCCESS);
}
