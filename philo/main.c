/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:17 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/24 19:49:27 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

long	ft_atoi(const char *str)
{
	long	n;
	int		sign;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	n = 0;
	while (*str >= 48 && *str <= 57)
	{
		n = n * 10 + (*str - 48);
		str++;
	}
	return (n * sign);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// mutex Lock / use avoid deadlock algo
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
//	eating(philo);
	usleep(10000);
	// mutex Unlock
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

int	ft_init_fork(t_arg *arg, pthread_mutex_t **fork)
{
	int	i;

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

int	ft_init_arg(t_arg *arg, int ac, char **av)
{
	arg->num_of_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (arg->num_of_philo <= 0 || arg->time_to_die <= 0
		|| arg->time_to_eat <= 0 || arg->time_to_sleep <= 0)
		return (ARG_ERR);
	if (ac == 6)
	{
		arg->must_eat_count = ft_atoi(av[5]);
		if (arg->must_eat_count <= 0)
			return (ARG_ERR);
	}
	return (SUCCESS);
}

int	ft_init_philo(t_arg arg, t_philo **philo, pthread_mutex_t *fork)
{
	int	i;

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
		pthread_create(&(*philo)[i].thread, NULL, philo_routine, &(*philo)[i]);
		(*philo)[i].arg = &arg;
		i++;
	}
	return (SUCCESS);
}

int	ft_errno(int errno, char *loc)
{ if (errno == 2)
		printf("Invalid Argument: %s\n", loc);
	else if (errno == 3)
		printf("pthread Error: %s\n", loc);
	else if (errno == 4)
		printf("malloc Error: %s\n", loc);
	else
		printf("etc Error: %s\n", loc);
	return (FAILURE);
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

int	main(int ac, char *av[])
{
	t_arg			arg;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	int				errno;

	if (ac != 5 && ac != 6)
		return (ft_errno(ARG_ERR, "input"));
	memset(&arg, 0, sizeof(t_arg));
	errno = ft_init_arg(&arg, ac, av);
	if (errno)
		return (ft_errno(errno, "ft_init_arg"));
	errno = ft_init_fork(&arg, &fork);
	if (errno)
		return (ft_errno(errno, "ft_init_forks"));
	errno = ft_init_philo(arg, &philo, fork);
	if (errno)
		return (ft_errno(errno, "ft_init_philo"));
	int i = 0;
	while (i < arg.num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	ft_destroy_mutex(arg.num_of_philo, fork);
	free(fork);
	free(philo);
}
