/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:07:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/08 15:03:14 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap"

void atob(t_deque *a, t_deque *b)
{
	check_sorted(a);
	if (a->size >= 100)
		division(a, b);
	else if (a->size < 100 && a->size > 10)
		division3(a, b);
	while (a->size > 3)
		pb(a, b);
	handmade(a);
	while (b->size)
		btoa(a, b);
	finish(a);
	return ;
}

int	main(int ac, char **av)
{
	t_deque	*a;
	t_deque	*b;

	if (ac < 2)
		return (0);
	a = deque_init();
	b = deque_init();
	check_argument(ac, av);
	check_string(ac, av);
	check_same(a);
	free_deque(a);
	free_deque(b);
	return (0);
}
