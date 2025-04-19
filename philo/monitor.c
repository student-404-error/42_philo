/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:55:12 by seong-ki          #+#    #+#             */
/*   Updated: 2025/04/19 15:55:14 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_done(t_arg *arg)
{
	pthread_mutex_lock(&arg->finish_mutex);
	if (arg->must_eat_count > 0 && arg->finished_eat == arg->num_of_philo)
	{
		arg->finish = 1;
		pthread_mutex_unlock(&arg->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&arg->finish_mutex);
	return (0);
}

static int	check_death(t_arg *arg, t_philo *ps, int idx)
{
	long long	now;
	int			died;

	pthread_mutex_lock(&ps[idx].state_mutex);
	now = ft_get_ms();
	died = (now - ps[idx].last_eat_time > arg->time_to_die);
	pthread_mutex_unlock(&ps[idx].state_mutex);
	if (died)
	{
		ft_print_philo_state(arg, &ps[idx], "died");
		pthread_mutex_lock(&arg->finish_mutex);
		arg->finish = 1;
		pthread_mutex_unlock(&arg->finish_mutex);
		return (1);
	}
	return (0);
}

void	ft_philo_check_finish(t_arg *arg, t_philo *ph)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&arg->finish_mutex);
		if (arg->finish)
		{
			pthread_mutex_unlock(&arg->finish_mutex);
			break ;
		}
		pthread_mutex_unlock(&arg->finish_mutex);
		if (all_done(arg))
			break ;
		i = 0;
		while (i < arg->num_of_philo)
			if (check_death(arg, ph, i++))
				return ;
		usleep(500);
	}
}
