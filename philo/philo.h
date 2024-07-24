/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:40:39 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/24 19:46:33 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define FAILURE 1
# define ARG_ERR 2
# define PTHREAD_ERR 3
# define MALLOC_ERR 4

typedef struct s_arg
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}	t_arg;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_arg			*arg;
}	t_philo;

// init functions
int		ft_init_arg(t_arg *arg, int ac, char **av);
int		ft_init_fork(t_arg *arg, pthread_mutex_t **fork);
int		ft_init_philo(t_arg arg, t_philo **philo, pthread_mutex_t *forks);
// utils functions
long	ft_atoi(const char *str);

#endif
