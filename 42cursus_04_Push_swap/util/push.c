/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:45:00 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/30 22:47:23 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pa(t_deque *a, t_deque *b)
{
	if (b->size == 0)
		return ;
	push_bottom(a, b->bottom->data);
	pop_bottom(b);
	write(1, "pa\n", 3);
}

void	pb(t_deque *a, t_deque *b)
{
	if (a->size == 0)
		return ;
	push_bottom(b, a->bottom->data);
	pop_bottom(a);
	write(1, "pb\n", 3);
}
