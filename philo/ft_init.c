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

int ft_init_fork(t_arg *arg, pthread_mutex_t **fork)
{
	int i;

	*fork = malloc(sizeof(pthread_mutex_t) * arg->num_of_philo);
	if (!(*fork))
		return (MALLOC_ERR);
	i = 0;
	while (i < arg->num_of_philo)
	{
		if (pthread_mutex_init(&(*fork)[i], NULL))
			return (PTHREAD_ERR);
		i++;
	}
	return (SUCCESS);
}

int ft_init_arg(t_arg *arg, int ac, char **av)
{
	arg->num_of_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->start_time = ft_get_ms();
	arg->finish = 0;
	if (arg->num_of_philo <= 0 || arg->time_to_die <= 0 || arg->time_to_eat <= 0 || arg->time_to_sleep <= 0)
		return (ARG_ERR);
	if (ac == 6)
	{
		arg->must_eat_count = ft_atoi(av[5]);
		if (arg->must_eat_count <= 0)
			return (ARG_ERR);
	}
	return (SUCCESS);
}

int ft_init_philo(t_arg arg, t_philo **philo, pthread_mutex_t *fork)
{
	int i;

	*philo = malloc(sizeof(t_philo) * arg.num_of_philo);
	if (!philo)
		return (MALLOC_ERR);
	i = 0;
	while (i < arg.num_of_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].eat_count = arg.must_eat_count;
		(*philo)[i].last_eat_time = 0; // 0 or get_time();
		(*philo)[i].left_fork = &fork[i];
		(*philo)[i].right_fork = &fork[(i + 1) % arg.num_of_philo];
		(*philo)[i].arg = &arg;
		i++;
	}
	return (SUCCESS);
}
