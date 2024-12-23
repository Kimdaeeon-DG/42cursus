/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:15:40 by daeekim           #+#    #+#             */
/*   Updated: 2024/12/23 20:15:41 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (!data->someone_died && !check_all_ate(data))
	{
		i = -1;
		while (++i < data->num_of_philos && !data->someone_died)
		{
			if (check_death(data, i))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
