/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:15:42 by daeekim           #+#    #+#             */
/*   Updated: 2024/12/23 20:15:44 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	print_status(data, philo->id, "is eating");
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	smart_sleep(data->time_to_eat, data);
	philo->eat_count++;
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2)
		smart_sleep(data->time_to_eat / 2, data);
	while (!data->someone_died)
	{
		eating(philo);
		if (data->must_eat_count != -1 && philo->eat_count >= data->must_eat_count)
			break;
		print_status(data, philo->id, "is sleeping");
		smart_sleep(data->time_to_sleep, data);
		print_status(data, philo->id, "is thinking");
		usleep(100);
	}
	return (NULL);
}
