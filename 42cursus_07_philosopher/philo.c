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
	
	// 시작 시간 동기화를 위해 대기
	while (get_time() < data->start_time)
		usleep(100);
		
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = data->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	
	// 짝수 번호 철학자는 약간 대기
	if (philo->id % 2 == 0)
		smart_sleep(1, data);

	while (!check_philosopher_death(data, philo->id - 1))
	{
		eating(philo);
		if (data->must_eat_count != -1 && 
			philo->eat_count >= data->must_eat_count)
			break;
		print_status(data, philo->id, "is sleeping");
		smart_sleep(data->time_to_sleep, data);
		print_status(data, philo->id, "is thinking");
		// 리소스 과다 사용 방지 및 교착 상태 방지를 위한 짧은 대기
		usleep(500);
	}
	return (NULL);
}
