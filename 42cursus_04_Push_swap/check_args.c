/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:19:18 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/14 18:35:32 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_duplication(int *unordered, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (unordered[i] == unordered[j])
			{
				free(unordered);
				print_error(1);
			}
			++j;
		}
	}
}

int	get_nums_count(char **av)
{
	int		i;
	int		j;
	char	**temp;
	int		nums_len;

	i = 0;
	nums_len = 0;
	while (av[++i])
	{
		temp = ft_split(av[i], ' ');
		if (!temp)
			print_error(1);
		else if (temp[0] == NULL)
			free_matrix(temp, 1);
		else
		{
			j = -1;
			while (temp[++j])
				check_num(temp[j], temp, &nums_len);
			free_matrix(temp, get_matrix_size(temp));
		}
	}
	return (nums_len);
}

int	check_args(int argc, char **argv)
{
	int	nums_count;

	nums_count = 0;
	if (argc < 2)
		print_error(0);
	nums_count = get_nums_count(argv);
	if (nums_count == 0)
		print_error(1);
	return (nums_count);
}
