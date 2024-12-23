#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);

	if (data->num_of_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->must_eat_count <= 0))
		return (1);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_of_philos;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL))
			return (1);
	}
	return (0);
}
