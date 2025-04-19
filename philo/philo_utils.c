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

int	ft_philo_start(t_arg *arg, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

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
