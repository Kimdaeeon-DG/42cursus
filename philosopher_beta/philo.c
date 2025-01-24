/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:23:39 by daeekim           #+#    #+#             */
/*   Updated: 2024/12/23 20:23:40 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	if (philo->id % 2)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(data, philo->id, "has taken a fork");
	}
}

static void	put_down_forks(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
	}
}

void	eating(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	take_forks(philo);

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	print_status(data, philo->id, "is eating");
	pthread_mutex_unlock(&philo->meal_mutex);
	
	smart_sleep(data->time_to_eat, data);
	philo->eat_count++;
	
	put_down_forks(philo);
}

static int	check_if_done(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	if (data->must_eat_count != -1 && philo->eat_count >= data->must_eat_count)
		return (1);
	return (0);
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
	
	if (data->num_of_philos == 1)
	{
		print_status(data, philo->id, "has taken a fork");
		return (NULL);
	}
	
	if (philo->id % 2 == 0)
		usleep(data->time_to_eat * 0.9);

	while (!check_death(data))
	{
		eating(philo);
		if (check_if_done(philo))
			break;
		
		print_status(data, philo->id, "is sleeping");
		smart_sleep(data->time_to_sleep, data);
		
		print_status(data, philo->id, "is thinking");
		if (data->num_of_philos % 2)
			usleep(500);
	}
	return (NULL);
}
