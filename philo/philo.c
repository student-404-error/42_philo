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

int ft_print_philo_state(t_arg *arg, t_philo *philo, char *state)
{
	long long now;
	int done;

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
static void handle_single(t_arg *arg, t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	ft_print_philo_state(arg, ph, "has taken a fork");
	ft_print_philo_state(arg, ph, "died");
	pthread_mutex_lock(&arg->finish_mutex);
	arg->finish = 1;
	pthread_mutex_unlock(&arg->finish_mutex);
	pthread_mutex_unlock(ph->left_fork);
}

static void eat_cycle(t_arg *arg, t_philo *ph)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;
	pthread_mutex_t *t;

	first = ph->left_fork;
	second = ph->right_fork;
	if (first > second)
	{
		t = first;
		first = second;
		second = t;
	}
	pthread_mutex_lock(first);
	ft_print_philo_state(arg, ph, "has taken a fork");
	pthread_mutex_lock(second);
	ft_print_philo_state(arg, ph, "has taken a fork");
	ft_print_philo_state(arg, ph, "is eating");
	pthread_mutex_lock(&ph->state_mutex);
	ph->last_eat_time = ft_get_ms();
	ph->eat_count++;
	pthread_mutex_unlock(&ph->state_mutex);
	ft_pass_time(arg->time_to_eat, arg);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

static int check_must(t_arg *arg, t_philo *ph)
{
	if (arg->must_eat_count > 0 && ph->eat_count >= arg->must_eat_count)
	{
		pthread_mutex_lock(&arg->finish_mutex);
		arg->finished_eat++;
		pthread_mutex_unlock(&arg->finish_mutex);
		return (1);
	}
	return (0);
}

int check_finish(t_arg *arg)
{
	pthread_mutex_lock(&arg->finish_mutex);
	if (arg->finish)
	{
		pthread_mutex_unlock(&arg->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&arg->finish_mutex);
	return (0);
}
void *ft_philo_routine(void *ptr)
{
	t_philo *ph;
	t_arg *arg;

	ph = ptr;
	arg = ph->arg;
	if (ph->id % 2 == 0)
		usleep(1000);
	while (!check_finish(arg))
	{
		if (check_finish(arg))
			break;
		if (arg->num_of_philo == 1)
		{
			handle_single(arg, ph);
			return (NULL);
		}
		eat_cycle(arg, ph);
		if (check_must(arg, ph))
			return (NULL);
		ft_print_philo_state(arg, ph, "is sleeping");
		ft_pass_time(arg->time_to_sleep, arg);
		ft_print_philo_state(arg, ph, "is thinking");
	}
	return (NULL);
}

int ft_philo_start(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
	int i;

	arg->start_time = ft_get_ms();
	i = 0;
	while (i < arg->num_of_philo)
	{
		philo[i].last_eat_time = arg->start_time;
		if (pthread_create(&philo[i].thread, NULL,
						   (void *)ft_philo_routine, &philo[i]) != 0)
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
