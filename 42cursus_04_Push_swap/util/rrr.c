/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:45:53 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 17:29:12 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
