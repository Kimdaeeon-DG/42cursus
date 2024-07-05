/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:29:14 by daeekim           #+#    #+#             */
/*   Updated: 2024/07/03 17:28:21 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rrb(t_deque *b)
{
	if (b->size < 2)
		return ;
	push_bottom(b, b->bottom->data);
	pop_top(b);
	write(1, "rrb\n", 4);
}
