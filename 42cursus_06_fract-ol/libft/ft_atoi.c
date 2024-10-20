/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:54:15 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/15 20:23:47 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	t;
	int	sign;
	int	result;

	t = 0;
	sign = 1;
	result = 0;
	while ((str[t] >= 9 && str[t] <= 13) || str[t] == 32)
		t++;
	if (str[t] == '-' || str[t] == '+')
	{
		if (str[t] == '-')
			sign *= -1;
		t++;
	}
	while (str[t] >= '0' && str[t] <= '9')
	{
		result *= 10;
		result += str[t] - '0';
		t++;
	}
	return (result * sign);
}
