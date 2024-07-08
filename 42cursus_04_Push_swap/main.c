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

int main(int ac, char **av)
{
	t_deque *deque_a;
	t_deque *deque_b;
	int		deque_size;

	if (argc < 2)
		return (0);
	if (check_integers(av))
		return (0);

	deque_b = NULL;
	deque_a = fill_deque(ac, av);
	deque_size = get_deque_size(deque_size);
	push_swap(&deque_a, &deque_b, deque_size);
	free_deque(&deque_a);
	free_deque(&deque_b);
	return (0);
}
