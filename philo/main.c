/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:17 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/25 18:29:14 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

int ft_print_philo_state(t_arg *arg, t_philo *philo, char *state)
{
	long long now;

	now = ft_get_ms();
	if (now == -1)
		return (-1);
	pthread_mutex_lock(&(arg->print));
	if (!(arg->finish))
		printf("%lld %d %s\n", now - arg->start_time, philo->id + 1, state);
	pthread_mutex_unlock(&(arg->print));
	return (0);
}

long long ft_get_ms(void)
{
	struct timeval tv;

	if (!gettimeofday(&tv, NULL))
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (-1);
}

void ft_pass_time(long long wait_time, t_arg *arg)
{
	long long start;
	long long now;

	start = ft_get_ms();
	while (!(arg->finish))
	{
		now = ft_get_ms();
		if ((now - start) >= wait_time)
			break;
		usleep(10);
	}
}

void *ft_philo_routine(t_arg *arg, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_philo_state(arg, philo, "has taken a fork");
	if (arg->num_of_philo != 1)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_philo_state(arg, philo, "has taken a fork");
		ft_print_philo_state(arg, philo, "is eating");
		philo->last_eat_time = ft_get_ms();
		philo->eat_count++;
		ft_pass_time((long long)arg->time_to_eat, arg);
		pthread_mutex_unlock(philo->right_fork);
	}
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int ft_errno(int errno, char *loc)
{
	if (errno == 2)
		printf("Invalid Argument: %s\n", loc);
	else if (errno == 3)
		printf("pthread Error: %s\n", loc);
	else if (errno == 4)
		printf("malloc Error: %s\n", loc);
	else
		printf("etc Error: %s\n", loc);
	return (errno);
}

int main(int ac, char *av[])
{
	t_arg arg;
	t_philo *philo;
	pthread_mutex_t *fork;
	int errno;

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
	errno = ft_philo_start(&arg, philo, fork);
	if (errno)
		return (ft_errno(errno, "ft_philo_start"));
	return (SUCCESS);
}
