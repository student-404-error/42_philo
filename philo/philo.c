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

void ft_philo_check_finish(t_arg *arg, t_philo *philo)
{
    int i;
    int done;
    long long now;

    pthread_mutex_lock(&(arg->finish_mutex));
    done = arg->finish;
    pthread_mutex_unlock(&(arg->finish_mutex));
    while (!done)
    {
        if ((arg->must_eat_count != 0) && (arg->num_of_philo == arg->finished_eat))
        {
            pthread_mutex_lock(&(arg->finish_mutex));
            arg->finish = 1;
            pthread_mutex_unlock(&(arg->finish_mutex));
            break;
        }
        i = 0;
        while (i < arg->num_of_philo)
        {
            now = ft_get_ms();
            pthread_mutex_lock(&(philo[i].state_mutex));
            if ((now - philo[i].last_eat_time) > arg->time_to_die)
            {
                pthread_mutex_unlock(&(philo[i].state_mutex));
                pthread_mutex_lock(&(arg->finish_mutex));
                arg->finish = 1;
                pthread_mutex_unlock(&(arg->finish_mutex));
                ft_print_philo_state(arg, &philo[i], "died");
                break;
            }
            pthread_mutex_unlock(&(philo[i].state_mutex));
            i++;
        }
    }
}

void *ft_thread(void *argv)
{
	t_arg *arg;
	t_philo *philo;
	philo = (t_philo *)argv;
	arg = philo->arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!(arg->finish))
	{
		ft_philo_routine(arg, philo);
		if (arg->must_eat_count == philo->eat_count)
		{
			arg->finished_eat++;
			break;
		}
		ft_print_philo_state(arg, philo, "is sleeping");
		ft_pass_time((long long)arg->time_to_sleep, arg);
		ft_print_philo_state(arg, philo, "is thinking");
	}
	return (0);
}
int ft_philo_start(t_arg *arg, t_philo *philo, pthread_mutex_t *fork)
{
	int i;

	i = 0;
	while (i < arg->num_of_philo)
	{
		philo[i].last_eat_time = ft_get_ms();
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
			return (1);
		i++;
	}
	ft_philo_check_finish(arg, philo);
	i = 0;
	while (i < arg->num_of_philo)
		pthread_join(philo[i++].thread, NULL);
	ft_free_thread_mutex(arg->num_of_philo, philo, fork);
	return (0);
}
