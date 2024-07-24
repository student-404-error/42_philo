/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:06:17 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/24 21:10:29 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

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
	ft_join_thread(arg.num_of_philo, philo);
	ft_free_thread_mutex(fork, philo);
	return (SUCCESS);
}
