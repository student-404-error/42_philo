/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:40:39 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/25 18:27:39 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define FAILURE 1
#define ARG_ERR 2
#define PTHREAD_ERR 3
#define MALLOC_ERR 4

typedef struct s_arg
{
	int num_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count;
	int finish;
	int finished_eat;
	long long start_time;
	pthread_mutex_t print;
} t_arg;

typedef struct s_philo
{
	int id;
	int eat_count;
	long long last_eat_time;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_arg *arg;
} t_philo;

// init functions
int ft_init_arg(t_arg *arg, int ac, char **av);
int ft_init_fork(t_arg *arg, pthread_mutex_t **fork);
int ft_init_philo(t_arg arg, t_philo **philo, pthread_mutex_t *forks);
// utils functions
long ft_atoi(const char *str);
void *ft_philo_routine(t_arg *arg, t_philo *philo);
void ft_join_thread(int num_of_philo, t_philo *philo);
void ft_destroy_mutex(int num_of_philo, pthread_mutex_t *fork);
void ft_free_thread_mutex(int num, t_philo *philo, pthread_mutex_t *fork);
long long ft_get_ms(void);
void ft_pass_time(long long wait_time, t_arg *arg);
void ft_philo_check_finish(t_arg *arg, t_philo *philo);
int ft_print_philo_state(t_arg *arg, t_philo *philo, char *state);
int ft_philo_start(t_arg *arg, t_philo *philo, pthread_mutex_t *fork);
#endif
