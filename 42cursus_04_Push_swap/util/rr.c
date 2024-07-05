/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:45:35 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 17:27:53 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr(t_deque *a, t_deque *b)
{
	if (a->size < 2 || b->size < 2)
		return ;
	push_bottom(a, a->top->data);
	pop_top(a);
	push_bottom(b, b->top->data);
	pop_top(b);
	write(1, "rr\n", 3);
}
