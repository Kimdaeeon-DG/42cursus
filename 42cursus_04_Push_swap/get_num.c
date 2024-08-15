/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:15:07 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/13 17:42:39 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bubble_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

int	*copy_sorted(int *arr, int size)
{
	int	*sorted;
	int	i;

	i = -1;
	sorted = (int *)malloc(sizeof(int) * size);
	if (!sorted)
	{
		free(arr);
		print_error(1);
	}
	while (++i < size)
		sorted[i] = arr[i];
	bubble_sort(sorted, size);
	return (sorted);
}

int	is_sorted(int *arr, int size)
{
	int	i;

	i = 0;
	if (size < 2)
		ft_free(arr, NULL, 0);
	while (++i < size)
	{
		if (arr[i] <= arr[i - 1])
			return (0);
	}
	return (1);
}

int	*get_nums(int nums_count, char **av)
{
	int		*num;
	char	**temp;
	int		index[3];

	index[0] = 0;
	index[2] = -1;
	num = (int *)malloc(sizeof(int) * nums_count);
	if (!num)
		print_error(1);
	while (av[++index[0]])
	{
		temp = ft_split(av[index[0]], ' ');
		if (!temp)
			print_error(1);
		else if (temp[0] == NULL)
			free_matrix(temp, 1);
		else
		{
			index[1] = -1;
			while (temp[++index[1]])
				num[++index[2]] = ft_atoi(temp[index[1]]);
			free_matrix(temp, get_matrix_size(temp));
		}
	}
	return (num);
}
