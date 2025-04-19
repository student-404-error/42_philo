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

#include "philo.h"

int	ft_print_philo_state(t_arg *arg, t_philo *philo, char *state)
{
	long long	now;
	int			done;

	now = ft_get_ms();
	if (now < 0)
		return (-1);
	pthread_mutex_lock(&arg->finish_mutex);
	done = arg->finish;
	pthread_mutex_unlock(&arg->finish_mutex);
	pthread_mutex_lock(&arg->print);
	if (!done || (strcmp(state, "died") == 0))
		printf("%lld %d %s\n", now - arg->start_time, philo->id + 1, state);
	pthread_mutex_unlock(&arg->print);
	return (0);
}

void	*ft_philo_routine(void *philo_ptr)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*tmp;
	t_philo			*philo;
	t_arg			*arg;

	philo = (t_philo *) philo_ptr;
	arg = philo->arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&arg->finish_mutex);
		if (arg->finish)
		{
			pthread_mutex_unlock(&arg->finish_mutex);
			break ;
		}
		pthread_mutex_unlock(&arg->finish_mutex);
		if (arg->num_of_philo == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			ft_print_philo_state(arg, philo, "has taken a fork");
			ft_print_philo_state(arg, philo, "died");
			pthread_mutex_lock(&arg->finish_mutex);
			arg->finish = 1;
			pthread_mutex_unlock(&arg->finish_mutex);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		first = philo->left_fork;
		second = philo->right_fork;
		if (first > second)
		{
			tmp = first;
			first = second;
			second = tmp;
		}
		pthread_mutex_lock(first);
		ft_print_philo_state(arg, philo, "has taken a fork");
		pthread_mutex_lock(second);
		ft_print_philo_state(arg, philo, "has taken a fork");
		ft_print_philo_state(arg, philo, "is eating");
		pthread_mutex_lock(&philo->state_mutex);
		philo->last_eat_time = ft_get_ms();
		philo->eat_count++;
		pthread_mutex_unlock(&philo->state_mutex);
		ft_pass_time(arg->time_to_eat, arg);
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		if (arg->must_eat_count > 0)
		{
			pthread_mutex_lock(&arg->finish_mutex);
			if (philo->eat_count >= arg->must_eat_count)
			{
				arg->finished_eat++;
				pthread_mutex_unlock(&arg->finish_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&arg->finish_mutex);
		}
		ft_print_philo_state(arg, philo, "is sleeping");
		ft_pass_time(arg->time_to_sleep, arg);
		ft_print_philo_state(arg, philo, "is thinking");
	}
	return (NULL);
}

void	ft_philo_check_finish(t_arg *arg, t_philo *philo)
{
	long long	now;

	now = ft_get_ms();
	while (1)
	{
		pthread_mutex_lock(&arg->finish_mutex);
		if (arg->finish)
		{
			pthread_mutex_unlock(&arg->finish_mutex);
			break ;
		}
		if (arg->must_eat_count && arg->finished_eat == arg->num_of_philo)
		{
			arg->finish = 1;
			pthread_mutex_unlock(&arg->finish_mutex);
			break ;
		}
		pthread_mutex_unlock(&arg->finish_mutex);
		while (i < arg->num_of_philo)
		{
			pthread_mutex_lock(&philo[i].state_mutex);
			if (now - philo[i].last_eat_time > arg->time_to_die)
			{
				pthread_mutex_unlock(&philo[i].state_mutex);
				ft_print_philo_state(arg, &philo[i], "died");
				pthread_mutex_lock(&arg->finish_mutex);
				arg->finish = 1;
				pthread_mutex_unlock(&arg->finish_mutex);
				return ;
			}
			pthread_mutex_unlock(&philo[i].state_mutex);
			i++;
		}
		usleep(500);
	}
}

int	ft_philo_start(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	arg->start_time = ft_get_ms();
	i = 0;
	while (i < arg->num_of_philo)
	{
		philo[i].last_eat_time = arg->start_time;
		if (pthread_create(&philo[i].thread, NULL,
				(void *) ft_philo_routine, &philo[i]) != 0)
			return (PTHREAD_ERR);
		i++;
	}
	usleep(100);
	ft_philo_check_finish(arg, philo);
	i = 0;
	while (i < arg->num_of_philo)
		pthread_join(philo[i++].thread, NULL);
	ft_free_thread_mutex(arg->num_of_philo, philo, forks);
	return (SUCCESS);
}
