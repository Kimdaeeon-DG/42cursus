#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
};

// init.c
int			init_data(t_data *data, int argc, char **argv);
int			init_mutex(t_data *data);
int			init_philos(t_data *data);

// utils.c
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_status(t_data *data, int id, char *status);
void		smart_sleep(long long time, t_data *data);
int			check_death(t_data *data, int i);

// philo.c
void		*philosopher(void *arg);
void		eating(t_philo *philo);

// monitor.c
void		*death_monitor(void *arg);

#endif
