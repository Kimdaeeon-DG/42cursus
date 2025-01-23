/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:23:30 by daeekim           #+#    #+#             */
/*   Updated: 2024/12/23 20:23:32 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

int	check_philosopher_death(t_data *data, int i)
{
	long long	current_time;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	current_time = get_time();
	if (current_time - data->philos[i].last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			print_status(data, data->philos[i].id, "died");
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
	}
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat_count == -1)
		return (0);
	finished = 0;
	i = -1;
	while (++i < data->num_of_philos)
	{
		if (data->philos[i].eat_count >= data->must_eat_count)
			finished++;
	}
	return (finished == data->num_of_philos);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (get_time() < data->start_time)
		usleep(100);
	while (!check_death(data) && !check_all_ate(data))
	{
		i = -1;
		while (++i < data->num_of_philos)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
