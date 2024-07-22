/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:45:00 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/22 10:40:00 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pa(t_deque *a, t_deque *b)
{
	if (b->size == 0)
		return ;
	push_top(a, b->top->data);
	pop_top(b);
	write(1, "pa\n", 3);
}

void	pb(t_deque *a, t_deque *b)
{
	if (a->size == 0)
		return ;
	push_top(b, a->top->data);
	pop_top(a);
	write(1, "pb\n", 3);
}
