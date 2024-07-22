/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:45:53 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/22 10:40:08 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rra(t_deque *a)
{
	if (a->size < 2)
		return ;
	push_top(a, a->bottom->data);
	pop_bottom(a);
	write(1, "rra\n", 4);
}

void	rrb(t_deque *b)
{
	if (b->size < 2)
		return ;
	push_bottom(b, b->bottom->data);
	pop_top(b);
	write(1, "rrb\n", 4);
}

void	rrr(t_deque *a, t_deque *b)
{
	if (a->size < 2 || b->size < 2)
		return ;
	push_top(a, a->bottom->data);
	pop_bottom(a);
	push_top(b, b->bottom->data);
	pop_bottom(b);
	write(1, "rrr\n", 4);
}
