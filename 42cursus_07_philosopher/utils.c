#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!data->someone_died)
		printf("%lld %d %s\n", get_time() - data->start_time, id, status);
	pthread_mutex_unlock(&data->print_mutex);
}

void	smart_sleep(long long time, t_data *data)
{
	long long	start;

	start = get_time();
	while (!data->someone_died)
	{
		if (get_time() - start >= time)
			break ;
		usleep(500);
	}
}

int	check_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n",
			get_time() - data->start_time, data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (0);
}
