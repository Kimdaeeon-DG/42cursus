/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:23:58 by daeekim           #+#    #+#             */
/*   Updated: 2025/01/24 00:23:30 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	int				all_ate;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_check_mutex;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

// init.c
int			init_data(t_data *data, int argc, char **argv);
int			init_mutex(t_data *data);
int			init_philos(t_data *data);

// utils.c
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_status(t_data *data, int id, char *status);
void		smart_sleep(long long time, t_data *data);

// philo.c
void		*philosopher(void *arg);
void		eating(t_philo *philo);

// monitor.c
int			check_death(t_data *data);
int			check_philosopher_death(t_data *data, int i);
void		*death_monitor(void *arg);

#endif
