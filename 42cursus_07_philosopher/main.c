/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:23:22 by daeekim           #+#    #+#             */
/*   Updated: 2024/12/23 20:23:24 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_program(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->num_of_philos)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->num_of_philos)
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

static int	create_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	i = -1;
	while (++i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
			philosopher, &data->philos[i]))
			return (1);
	}
	if (pthread_create(&monitor, NULL, death_monitor, data))
		return (1);
	i = -1;
	while (++i < data->num_of_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argc, argv))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (init_mutex(&data) || init_philos(&data))
	{
		clean_program(&data);
		printf("Error: initialization failed\n");
		return (1);
	}
	if (create_threads(&data))
	{
		clean_program(&data);
		printf("Error: thread creation failed\n");
		return (1);
	}
	clean_program(&data);
	return (0);
}
