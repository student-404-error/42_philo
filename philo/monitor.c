
#include "philo.h"

static int all_done(t_arg *arg)
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

static int check_death(t_arg *arg, t_philo *ps, int idx)
{
    pthread_mutex_lock(&ps[idx].state_mutex);
    long long now = ft_get_ms();
    int died = (now - ps[idx].last_eat_time > arg->time_to_die);
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

void ft_philo_check_finish(t_arg *arg, t_philo *ph)
{
    while (1)
    {
        pthread_mutex_lock(&arg->finish_mutex);
        if (arg->finish)
        {
            pthread_mutex_unlock(&arg->finish_mutex);
            break;
        }
        pthread_mutex_unlock(&arg->finish_mutex);
        if (all_done(arg))
            break;
        for (int i = 0; i < arg->num_of_philo; i++)
            if (check_death(arg, ph, i))
                return;
        usleep(500);
    }
}