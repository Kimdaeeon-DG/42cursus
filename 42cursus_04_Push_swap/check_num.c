/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:41:11 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/14 18:41:41 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_num2(const char *str)
{
	if (*str == '-' || *str == '+')
    {
		str++;
	    if (*str == '-' || *str == '+' || *str == '\0' || *str == '0')
		    return (0);
    }
	return (1);
}

int	check_num1(const char *str)
{
	int			len_num;
	int			sign;
	long long	result;

	len_num = 0;
	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
		len_num++;
	}
	result = result * sign;
	if (*str != '\0' || len_num > 10 \
			|| result > 2147483647 || result < -2147483648)
		return (0);
	return (1);
}

void	check_num(char *num, char **temp, int *nums_count)
{
	*nums_count += 1;
	if (!check_num1(num) || !check_num2(num))
		free_and_exit(temp, get_matrix_size(temp), 1);
}
