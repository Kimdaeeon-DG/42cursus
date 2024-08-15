/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/14 15:32:41 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	int		nums_len;
	int		*array;
	int		*sorted;
	t_deque	a;
	t_deque	b;

	init_deque(&b, &sorted);
	nums_len = check_args(ac, av);
	array = get_nums(nums_len, av);
	check_duplication(array, nums_len);
	if (is_sorted(array, nums_len))
		ft_free(array, sorted, 0);
	sorted = copy_sorted(array, nums_len);
	if (nums_len == 2)
		sort2(array, sorted);
	else if (nums_len >= 3)
	{
		make_deque_a(&a, array, sorted, nums_len);
		if (nums_len >= 3 && nums_len <= 5)
			sort35(nums_len, &a, &b);
		else
			algorithm(&a, &b, nums_len);
	}
	free_all(&a, &b, array, sorted);
	return (0);
}
