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
	int	is_dead;

	pthread_mutex_lock(&data->death_mutex);
	is_dead = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (is_dead);
}

int	check_philosopher_death(t_data *data, int i)
{
	long long	current_time;
	long long	last_meal;
	int			is_dead;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	current_time = get_time();
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);

	is_dead = (current_time - last_meal > data->time_to_die);
	if (is_dead)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			print_status(data, data->philos[i].id, "died");
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->must_eat_count == -1)
		return (0);

	all_ate = 1;
	i = -1;
	while (++i < data->num_of_philos)
	{
		if (data->philos[i].eat_count < data->must_eat_count)
		{
			all_ate = 0;
			break;
		}
	}
	return (all_ate);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	usleep(100);

	while (!check_death(data))
	{
		if (check_all_ate(data))
			break;
		i = -1;
		while (++i < data->num_of_philos)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
