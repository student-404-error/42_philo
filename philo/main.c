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

long long	ft_get_ms(void)
{
	struct timeval	tv;

	if (!gettimeofday(&tv, NULL))
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (-1);
}

void	ft_pass_time(long long wait_time, t_arg *arg)
{
	long long	start;
	int			done;

	start = ft_get_ms();
	while (1)
	{
		pthread_mutex_lock(&arg->finish_mutex);
		done = arg->finish;
		pthread_mutex_unlock(&arg->finish_mutex);
		if (done)
			break ;
		if (ft_get_ms() - start >= wait_time)
			break ;
		usleep(10);
	}
}

int	ft_errno(int errno, char *loc)
{
	if (errno == ARG_ERR)
		printf("Invalid Argument: %s\n", loc);
	else if (errno == PTHREAD_ERR)
		printf("pthread Error: %s\n", loc);
	else if (errno == MALLOC_ERR)
		printf("malloc Error: %s\n", loc);
	else
		printf("etc Error: %s\n", loc);
	return (errno);
}

int	main(int ac, char *av[])
{
	pthread_mutex_t	*forks;
	t_arg			arg;
	t_philo			*philo;
	int				err;

	if (ac != 5 && ac != 6)
		return (ft_errno(ARG_ERR, "input"));
	memset(&arg, 0, sizeof(arg));
	err = ft_init_arg(&arg, ac, av);
	if (err)
		return (ft_errno(err, "ft_init_arg"));
	err = ft_init_fork(&arg, &forks);
	if (err)
		return (ft_errno(err, "ft_init_fork"));
	err = ft_init_philo(&arg, &philo, forks);
	if (err)
	{
		ft_destroy_mutex(arg.num_of_philo, forks);
		free(forks);
		return (ft_errno(err, "ft_init_philo"));
	}
	err = ft_philo_start(&arg, philo, forks);
	if (err)
		return (ft_errno(err, "ft_philo_start"));
	return (SUCCESS);
}
