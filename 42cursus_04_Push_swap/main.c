/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/08/09 17:33:44 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_deque	*a;
	t_deque	*b;
	int		size;

	if (ac < 2)
		return (0);
	a = deque_init();
	insert_value(av, a);
	b = deque_init();
	size = a->size;
	if (size == 2)
		sort2(a);
	else if (size >= 3)
	{
		if (size >= 3 && size <= 5)
			sort35(size, a, b);
		else
			algorithm(a, b, size);
	}
	free_all(a, b);
	return (0);
}
